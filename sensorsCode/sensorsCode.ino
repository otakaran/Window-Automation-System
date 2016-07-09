/*
THE AUTOMATIC COVER
Version 1.05

ChangeLog:
1.0 - Compleated all sensor + LCD work.
1.05 - Started work on stepper motor output

Ports:
Pressure - Analog pin A0
Humidity (DHT22) - Digital pin 8 (3.3v)
LCD - Digital pins 2, 3, 4, 5, 11, and 12

NEEDED LIBARIES:
DHT Sensor Libary: https://github.com/adafruit/DHT-sensor-library
*/

// INPUT

// INITIALIZE HUMIDITY SENSOR
#include "DHT.h"
#define DHTPIN 8     // Humidity digital pin
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor.

// INITIALIZE LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

// INITIALIZE STEPPER
#include <Stepper.h>
const int stepsPerRevolution = 200;  // Number of steps per revolution
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); // Pins for stepper motor

// INITIALIZE VARIABLES
bool isRaining;
int pressure;
float humidity;
unsigned long previousMillis = 0;
const long interval = 60000; // Rain update frequency (ms)

void checkHumidity() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Checking");
  lcd.setCursor(0,1);
  lcd.print("humidity");
  delay(3000);
  float humidity = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  if (humidity > 50) {

  // IF PRESSURE DETECTED AND HUMIDITY > 90%, isRaining = true

    bool isRaining = true;
    Serial.print("Rain Detected");
    Serial.println("");
    lcd.clear();
    lcd.print("Rain");
    lcd.setCursor(0,1);
    lcd.print("detected");
    delay(5000);
  }
  else {

    // IF PRESSURE DETECTED AND HUMIDITY < 90%, isRaining = False

    bool isRaining = false;
    Serial.print("False positive - humidity override");
    Serial.println("");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Humidity");
    lcd.setCursor(0,1);
    lcd.print("Override");
    delay(5000);
    }
}

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(60);
  dht.begin();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Auto Cover");
  lcd.setCursor(0,1);
  lcd.print("Started");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop() {

// CHECK PRESSURE

 int pressure = analogRead(A0);
 delay(100);

 // IF PRESSURE DETECTED, CHECK HUMIDITY

 if (pressure > 50) {
  Serial.print("Pressure: ");
  Serial.println(pressure);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Rain drop");
  lcd.setCursor(0,1);
  lcd.print("detected");
  delay(1000);
  checkHumidity();
  }

// RAIN UPDATING

unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= interval) {
  previousMillis = currentMillis;
  if (isRaining = true) {
    checkHumidity();
    }
  }

// OUTPUT

if (isRaining = true) {
  Serial.print("Opening Cover");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Opening");
  lcd.setCursor(0,1);
  lcd.print("cover");
  myStepper.step(stepsPerRevolution);
  }

}
