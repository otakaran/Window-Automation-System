#include <LiquidCrystal.h>
// See http://arduino.cc/en/Reference/LiquidCrystal

//Declare pin functions on Redboard
#define stp 7
#define dir 6
#define MS1 8
#define EN  1

LiquidCrystal lcd(12,11,5,4,3,2);
int strip = 2;
int optionSelector = 0;
int variableChanger = 1;
int stripState = 0;
int selectedOption = 0;
int input = 0;

//Declare variables for functions
char user_input;
int x;
int y;
int state;

void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(stripState, INPUT);
  Serial.begin(9600);

  pinMode(dir, OUTPUT);
  pinMode(stp, OUTPUT);
  pinMode(EN, OUTPUT);
  resetEDPins(); //Set step, direction, microstep and enable pins to default states
}

//Reset Easy Driver pins to default states
void resetEDPins()
{
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(EN, HIGH);
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

//Forward/reverse stepping function
void ForwardBackwardStep()
{
  for(x= 1; x<5; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    //Read direction pin state and change it
    state=digitalRead(dir);
    if(state == HIGH)
    {
      digitalWrite(dir, LOW);
    }
    else if(state ==LOW)
    {
      digitalWrite(dir,HIGH);
    }
    
    for(y=1; y<1000; y++)
    {
      digitalWrite(stp,HIGH); //Trigger one step
      delay(1);
      digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
      delay(1);
    }
  }
}

void loop()
{
  // Set button inputs every loop
  stripState = analogRead(strip);
  selectedOption = analogRead(optionSelector);
  input = analogRead(variableChanger);

  selectedOption = map(selectedOption, 10, 1023, 1, 7);  // This may seem arbitrary but it works
  menu(selectedOption, stripState, variableChanger);

  lcd.setCursor(0,1);
  lcd.print("Red: ");
  lcd.print(stripState);
  lcd.print(" IN: ");
  lcd.print(input);
  
  delay(10);  // Adjust this based on how much the LCD flickers
  lcd.clear();
}

int menu(int selectedOption, int stripState, int variableChanger)
{
  switch (selectedOption)
  {
    case 1:
      lcd.setCursor(0,0);
      lcd.print("SYSTEM TIME");
      if (stripState < 240)
      {
        StepForwardDefault();
      }
      break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("CLOSE TIME");
      break;
    case 3:
      lcd.setCursor(0,0);
      lcd.print("OPEN TIME");
      break;
    case 4:
      lcd.setCursor(0,0);
      lcd.print("SMART RAIN");
      break;
    case 5:
      lcd.setCursor(0,0);
      lcd.print("SMART TEMP");
      break;
    case 6:
      lcd.setCursor(0,0);
      lcd.print("WIP");
      break;
    default:
      //
    break;
  }
}
