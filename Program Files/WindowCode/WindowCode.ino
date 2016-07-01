/*
 * WindowCode.ino
 * This program runs window automation on an Arduino
 * Copyright 2016 Otakar Andrysek and Braeden Day
 */

/*
 *  I'm going to add more comments to the docstring as time 
 *  goes on so that our entire program can be outlined here.
 */

void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);   // Turn on the LED
  delay(1000);              // Wait for one second
  digitalWrite(13, LOW);    // Turn off the LED
  delay(1000);              // Wait for one second
}
