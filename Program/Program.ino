//
//
//  WIP Docstring
//
//
//

// Default library inclusion
#include <LiquidCrystal.h>
#include <SFE_BMP180.h>
#include <Wire.h>

//Declare pin functions on Redboard
#define stp 7
#define dir 6
#define force 1
#define potentiometer 0
LiquidCrystal lcd(12,11,5,4,3,2);

//Declare variables for functions
int x;
int forceRead;
int potentialState;
char status;
double Tstart; 
double Pstart;
int k = 0;
bool openState = false;

// You will need to create an SFE_BMP180 object, here called "pressure"
SFE_BMP180 pressure;

//This function sets up pins and the initial sensor readings
void setup()
{
  Serial.begin(9600);   // Just for testing; remove later RMLA
  Serial.println("REBOOT");   // Also just for testing RMLA
  lcd.begin(16, 2); 
  pressure.begin();
  lcd.clear();
  Tstart = checkTemperature();  // Take initial readings
  Pstart = checkPressure(Tstart); // Take initial readings
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
  for(x = 1; x < 5000; x++)  //Loop the forward stepping enough times for motion to be visible
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
  for(x = 1; x < 5000; x++)  //Loop the stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
}

// Checks temperature
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

// Check pressure (needs temperature)
double checkPressure(double T)  {
  double P;
  status = pressure.startPressure(3);
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed pressure measurement:
    // Note that the measurement is stored in the variable P.
    // Note also that the function requires the previous temperature measurement (T).
    // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
    // Function returns 1 if successful, 0 if failure.

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

// The bulk of the code. Here is where the program decides if the window should close / open.
bool operateWindow(double T, double P, double Pstart, int forceRead, bool openState)  {
  lcd.setCursor(14,1);
  if (openState == false)   // Runs if window is closed
  {
    if (forceRead < 990 && P + 2 > Pstart)
    {
      lcd.print("11");
      return false;
    }
    else if (forceRead < 990 && P + 2 < Pstart)
    {
      lcd.print("12");
      return false;
    }
    else if (forceRead > 990 && P + 2 > Pstart)
    {
      lcd.print("13");
      return false;
    }
    else if (forceRead > 990 && P + 2 < Pstart)
    {
      lcd.print("14");
      StepForwardDefault();   // OPEN ER' UP
      return true;
    }
    else
    {
      lcd.print("1X");
    }
  }
  else  // In this situation the window is open
  {
    if (forceRead < 990 && P > Pstart)
    {
      lcd.print("21");
      if (k > 100)
      {
        ReverseStepDefault();
        k = 0;
        return false;
      }
      else
      {
        k++;
        return true;
      }
    }
    else if (forceRead < 990 && P < Pstart)
    {
      lcd.print("22");
      return true;
    }
    else if (forceRead > 990 && P + 2 > Pstart)
    {
      lcd.print("23");
      return true;
    }
    else if (forceRead > 990 && P + 2 < Pstart)
    {
      lcd.print("24");
      return true;
    }
    else
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
