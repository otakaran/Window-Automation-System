// Default library inclusion
#include <LiquidCrystal.h>

//Declare pin functions on Redboard
#define stp 7
#define dir 6
#define forceClose 1
#define forceFar 2
#define potentiometer 0
LiquidCrystal lcd(12,11,5,4,3,2);

//Declare variables for functions
int x;
int force1;
int force2;
int potentialState;

void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(dir, OUTPUT);
  pinMode(stp, OUTPUT);
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW); //Set step, direction, microstep and enable pins to default states
}

//Default microstep mode function
void StepForwardDefault()
{
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  for(x= 1; x<200; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
}

//Reverse default microstep mode function
void ReverseStepDefault()
{
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  for(x= 1; x<1000; x++)  //Loop the stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
}

void loop()
{
  // Set button inputs every loop
  force1 = forceClose;
  force2 = forceFar;
  potentialState = potentiometer;

  lcd.setCursor(0,1);
  lcd.print("PR: ");
  lcd.print(" IN: ");
  
  delay(10);  // Adjust this based on how much the LCD flickers
  lcd.clear();
}
