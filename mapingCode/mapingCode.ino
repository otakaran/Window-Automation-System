#include <LiquidCrystal.h>

// See http://arduino.cc/en/Reference/LiquidCrystal
// for more information:

LiquidCrystal lcd(12,11,5,4,3,2);

void setup()
{
  // The LiquidCrystal library can be used with many different
  // LCD sizes. We're using one that's 2 lines of 16 characters,
  // so we'll inform the library of that:

  lcd.begin(16, 2);

  lcd.clear();

  // Now we'll display a message on the LCD!

  // Just as with the Arduino IDE, there's a cursor that
  // determines where the data you type will appear. By default,
  // this cursor is invisible, though you can make it visible
  // with other library commands if you wish.

  // When the display powers up, the invisible cursor starts 
  // on the top row and first column.

  

 
}

void loop()
{
  int cursorPos = analogRead(0);
  cursorPos = map(cursorPos, 10, 1010, 1,6);
  lcd.print("Braeden is cool!");
  lcd.setCursor(3,1);
  
  
  // Now we'll print the number of seconds (millis() / 1000)
  // since the Arduino last reset:

  lcd.print("Value=");
  lcd.print(cursorPos);
  delay(100);
  lcd.clear();
  
  /*lcd.setCursor(0,1);   // Set the cursor to the position
  lcd.print("       "); // Erase the largest possible number
  lcd.setCursor(0,1);   // Reset the cursor to the original position
  lcd.print(millis()/1000); // Print our value*/

  // http://arduino.cc/en/Reference/LiquidCrystal
 
	}