#include <LiquidCrystal.h>
// See http://arduino.cc/en/Reference/LiquidCrystal

LiquidCrystal lcd(12,11,5,4,3,2);

void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
}

void loop()
{
  int cursorPos = analogRead(0);
  cursorPos = map(cursorPos, 10, 1010, 1,6);
  lcd.print("Braeden is cool!");
  lcd.setCursor(3,1);
  lcd.print("Value=");
  lcd.print(cursorPos);
  delay(100);
  lcd.clear();
	}
