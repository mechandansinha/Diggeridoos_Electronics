/*
Author - Chandan Sinha
Date - March 15, 2023

Program to run Adafruit NeoPixel LED strip using Arduino Mega. We are using Adafruit-NeoPixel library.
Library usage can be found here - https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use

Follow strandtest.ino sketch from the Example folder. As instructed, I used a 470 Ohm resistor in series with the data pin from
Arduino Mega (Pin 6) to PWM input of the LED strip. 

KEEP THE POWER SUPPLY TO 5-5.5V. DO NOT EXCEED 6V IN ANY CASE. 
*/

#include <Adafruit_NeoPixel.h>
#define LED_PIN    6
#define LED_COUNT 60

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  // put your main code here, to run repeatedly:
  colorWipe(strip.Color(255,   0,   0), 50); // Red
  colorWipe(strip.Color(  0, 255,   0), 50); // Green
  colorWipe(strip.Color(  0,   0, 255), 50); // Blue
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
