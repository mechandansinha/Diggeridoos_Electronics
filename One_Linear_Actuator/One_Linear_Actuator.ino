/*
Author - Chandan Sinha
Date - March 1, 2023

This code just activates the keyes-SR1y relay module which is used to close the switch for 
bigger OONO F-1021 Forward & Reverse Relay Module (connected to 120VAC - 24VDC power supply)
to drive one Progressive Automation PA-17P-4-2000 Linear Actuator
*/

#define FORWARD 50 // Connect the smaller relay module to this pin on Arduino Mega 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(FORWARD, OUTPUT);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(FORWARD, HIGH);
  delay(2000);
  digitalWrite(FORWARD, LOW);
  delay(1000);
}
