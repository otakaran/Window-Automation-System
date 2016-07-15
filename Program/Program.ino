//
// Window Automation System Code
//
// Created July 8, 2016 by the WAS team
// Copyright © 2016 Otakar Andrysek
// Official Invention Bootcamp Project
//
// This program runs on the arduino RedBoard and automates the opening and closing of a window based
// on the weather conditions. Currently implemented weather detection includes a barometric pressure
// sensor and a force sensor to detect raindrops. Both of these sensors must be triggered for the w-
// indow to open. After the window closes and if the pressure increases and no raindrops are detect-
// ed for a certain amount of time the window will automatically open again.
//
// This program revolves around using a stepper motor to operate a rope pully system. Other systems
// may be used with modification.
//

// Default library inclusion
#include <LiquidCrystal.h>  // Used to control the LCD
#include <SFE_BMP180.h> // Barometric pressure / temperature sensor
#include <Wire.h> // I have no idea why this is needed

// Declare pin functions on Redboard
#define stp 7 // This pin controls the amount of stepping the stepper motor does
#define dir 6 // This pin determines the direction of movement for the stepper motor
#define force 1 // The force sensor input
LiquidCrystal lcd(12,11,5,4,3,2); // Creates a 'LiquidCrystal' object to be used later

// Declare variables for functions
// Many of these variables may (and should) be converted to local variables
int x;  // Incrementer
int forceRead;  // Force sensor input
char status;  // Used to detect f the bar sensor is done reading and other fun stuff
double Tstart; // Initial temperature reading
double Pstart;  // Initial pressure reading
int k = 0;  // [DEPREKATED]?????!!!!!!
bool openState = false; // Is the window open?

// You will need to create an SFE_BMP180 object, here called "pressure"
SFE_BMP180 pressure;

//This function sets up pins and the initial sensor readings
void setup()
{
  // LCD and sensor initilization
  Serial.begin(9600);   // Just for testing; remove later RMLA
  Serial.println("REBOOT");   // Also just for testing RMLA
  lcd.begin(16, 2); 
  pressure.begin(); // Initializes the pressure/tmp sensor
  lcd.clear();

  // Take initial readings
  Tstart = checkTemperature();  
  Pstart = checkPressure(Tstart);
  
  // Sets pins to correct mode
  pinMode(dir, OUTPUT);
  pinMode(stp, OUTPUT);
  
  // Clears the motor and sets it to a default mode
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
}

//Default microstep mode function [OPEN WINDOW]
void StepForwardDefault()
{
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  for(x = 1; x < 13000; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
}

//Reverse default microstep mode function [CLOSE WINDOW]
void ReverseStepDefault()
{
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  for(x = 1; x < 13000; x++)  //Loop the stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
}

// This function reads the temperature from the BMP 180 sensor.
// The function waits for reading to complete before it stores the raw input into the variable T
int checkTemperature() {
  double T;
  status = pressure.startTemperature();
  if (status != 0)
  {
      // Wait for the measurement to complete:
      delay(status);
      status = pressure.getTemperature(T);
      if (status != 0)  {
        // Print out the measurement:
        lcd.print(" T:");
        lcd.print((9.0/5.0)*T+32.0,2);
        return(T);
    }
  }
}

// Retrieve the completed pressure measurement:
// Note that the measurement is stored in the variable P.
// Note also that the function requires the previous temperature measurement (T).
// Function returns 1 if successful, 0 if failure.
double checkPressure(double T)  {
  double P;
  status = pressure.startPressure(3);
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    status = pressure.getPressure(P,T);
    if (status != 0)
    {
      // Print out the measurement:
      lcd.print("P: ");
      lcd.print(P,2);
      lcd.print(" mb");
      return(P);
    }
  }
}

// The bulk of the code. Here is where the program decides if the window should close / open
bool operateWindow(double T, double P, double Pstart, int forceRead, bool openState)  {
  lcd.setCursor(14,1);
  if (openState == false)   // Runs if window is closed
  {
    if (forceRead < 990 && P + 2 > Pstart)  // If window is closed, no raindrops, no pressure drop
    {
      lcd.print("11");
      return false;
    }
    else if (forceRead < 990 && P + 2 < Pstart) // If window is closed, no raindrops, pressure drop
    {
      lcd.print("12");
      return false;
    }
    else if (forceRead > 990 && P + 2 > Pstart) // If window is closed, raindrops, no pressure drop
    {
      lcd.print("13");
      return false;
    }
    else if (forceRead > 990 && P + 2 < Pstart) // If window is closed, raindrops, pressure drop
    {
      lcd.print("14");
      StepForwardDefault();   // CLOSE ER' UP
      return true;
    }
    else    // Error 1 condition (Just for debugging)[RMLA?]
    {
      lcd.print("1X");
    }
  }
  else  // In this situation the window is open
  {
    if (forceRead < 990 && P > Pstart)  // If window is open, no raindrop, pressure back up
    {
      lcd.print("21");
      if (k > 25)    // Once 100 (ticks) occurs with no rain or pressure the window will open
      {
        ReverseStepDefault();
        k = 0;
        return false;
      }
      else    // If timer is not triggered increment it
      {
        k++;
        return true;
      }
    }
    else if (forceRead < 990 && P < Pstart) // If window is open, no raindrop, pressure still down
    {
      lcd.print("22");
      k = 0;
      return true;
    }
    else if (forceRead > 990 && P + 2 > Pstart) // If window is open, raindrop detected, pressure back up
    {
      lcd.print("23");
      k = 0;
      return true;
    }
    else if (forceRead > 990 && P + 2 < Pstart) // If window is open, raindrop detected, pressure still down
    {
      lcd.print("24");
      k = 0;
      return true;
    }
    else    // Error 2 condition (Just for debugging)[RMLA?]
    {
      lcd.print("2X");
    }
  }
}

// The loop that launches functions and also runs some basic setup every loop
void loop()
{
  // Set button inputs every loop
  forceRead = analogRead(force);

  // Pressure Sensor Stuff
  double T,P;

  // Simple Sensors
  lcd.setCursor(0,0);
  lcd.print("F: ");
  lcd.print(forceRead);
  T = checkTemperature();
  lcd.setCursor(0,1);
  P = checkPressure(T);

  //Serial.println(Pstart);
  //Serial.println(P);
  Serial.println(openState);

  openState = operateWindow(T, P, Pstart, forceRead, openState);

  // Delay and clear the LCD
  delay(200);  // Adjust this based on how much the LCD flickers
  lcd.clear();
}

//
//
// EOF
