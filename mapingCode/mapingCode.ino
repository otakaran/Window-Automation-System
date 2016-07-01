#include <LiquidCrystal.h>
// See http://arduino.cc/en/Reference/LiquidCrystal

LiquidCrystal lcd(12,11,5,4,3,2);
int redButton = 9;
int blueButton = 8;
int redState = 0;
int blueState = 0;

int time = 0;
int closeTime = 0;

void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(redState, INPUT);
  pinMode(blueState, INPUT);
}

void loop()
{
  redState = digitalRead(redButton);
  blueState = digitalRead(blueButton);
  
  int cursorPos = analogRead(0);
  int selection = 0;
  cursorPos = map(cursorPos, 10, 1010, 1,6);
  lcd.print(cursorPos);
  delay(100);
  lcd.clear();
  menu(cursorPos);
  delay(200);
  lcd.setCursor(3,1);
  lcd.print("Value: ");
}

void menu(int cursorPos)
{
  switch (cursorPos) {
    case 1:
      lcd.setCursor(0,0);
      lcd.print("Set Time");
      lcd.setCursor(11,1);
      if (redState == HIGH)
      {
    time = time + 1;
    lcd.print(time);
      } 
      else if (blueState == HIGH)
      {
        time = time - 1;
        lcd.print(time);
      }
      else
      {
        lcd.print("ERROR TIME: ");
      }
      break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("Set close time");
      break;
    case 3:
      lcd.setCursor(0,0);
      lcd.print("Close on Rain");
      break;
    case 4:
      lcd.setCursor(0,0);
      lcd.print("Close on ____");
      break;
    case 5:
      lcd.setCursor(0,0);
      lcd.print("Code on ______");
      break;
    case 6:
      lcd.setCursor(0,0);
      lcd.print("Shutdown");
      break;
    default: 
      lcd.setCursor(0,0);
      lcd.print("ERROR");
    break;
  }
}
