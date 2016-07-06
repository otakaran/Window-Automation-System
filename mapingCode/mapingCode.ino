#include <LiquidCrystal.h>
// See http://arduino.cc/en/Reference/LiquidCrystal

LiquidCrystal lcd(12,11,5,4,3,2);
int redButton = 9;
int optionSelector = 0;
int variableChanger = 1;

int redButtonState = 0;
int selectedOption = 0;
int input = 0;

int dirpin = 6;
int steppin = 7;

void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(redButtonState, INPUT);
  Serial.begin(9600);

  pinMode(dirpin, OUTPUT);
  pinMode(steppin, OUTPUT);
}

void spin()
{
  int i;
  digitalWrite(dirpin, LOW);     // Set the direction.
  delay(100);
  for (i = 0; i<4000; i++)       // Iterate for 4000 microsteps.
  {
    digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delayMicroseconds(500);      // This delay time is close to top speed for this
  }                              // particular motor. Any faster the motor stalls.
  digitalWrite(dirpin, HIGH);    // Change direction.
  delay(100);
  for (i = 0; i<4000; i++)       // Iterate for 4000 microsteps
  {
    digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delayMicroseconds(500);      // This delay time is close to top speed for this
  }                              // particular motor. Any faster the motor stalls.
}

void loop()
{
  // Set button inputs every loop
  redButtonState = digitalRead(redButton);
  selectedOption = analogRead(optionSelector);
  input = analogRead(variableChanger);

  selectedOption = map(selectedOption, 10, 1023, 1, 7);  // This may seem arbitrary but it works
  menu(selectedOption, redButtonState, variableChanger);

  lcd.setCursor(0,1);
  lcd.print("Red: ");
  lcd.print(redButtonState);
  lcd.print(" IN: ");
  lcd.print(input);
  
  delay(50);  // Adjust this based on how much the LCD flickers
  lcd.clear();
}

int menu(int selectedOption, int redButtonState, int variableChanger)
{
  switch (selectedOption)
  {
    case 1:
      lcd.setCursor(0,0);
      lcd.print("SYSTEM TIME");
      spin();
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

