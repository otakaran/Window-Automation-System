#include <LiquidCrystal.h>
// See http://arduino.cc/en/Reference/LiquidCrystal
#include <time.h>

LiquidCrystal lcd(12,11,5,4,3,2);
int redButton = 9;
int optionSelector = 0;
int variableChanger = 1;

int redButtonState = 0;
int selectedOption = 0;
int input = 0;

void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(redButtonState, INPUT);
  Serial.begin(9600);
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

