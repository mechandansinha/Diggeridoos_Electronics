/*
Author - Chandan Sinha
Date - February 26, 2023
Demonstration of reading multiple I2C based devices using I2C Multiplexer TCA9548A.
Sensors used - 2 MCP9808 temperature sensor connected on ports (SCA,SDA) 0 and 1 of the multiplexer. 
Because of identical sensor with same default I2C address, we reset address of one of those to 0x19.
*/

#include <Wire.h>
#include "Adafruit_MCP9808.h"

#define TCAADDR 0x70
#define SENSOR1_ADDRESS 0x18
#define SENSOR2_ADDRESS 0x19

Adafruit_MCP9808 tempsensor1 = Adafruit_MCP9808();
Adafruit_MCP9808 tempsensor2 = Adafruit_MCP9808();

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  tempsensor1.begin(SENSOR1_ADDRESS);
  tempsensor2.begin(SENSOR2_ADDRESS);

  tempsensor1.setResolution(0);
  tempsensor2.setResolution(0);

  tcaselect(0);
  if(!tempsensor1.begin())
  {
    Serial.println("Sensor1: Ooops, no MCP9808 detected ... Check your wiring!");
    while(1);
  }

  tcaselect(1);
  if(!tempsensor2.begin())
  {
    Serial.println("Sensor2: Ooops, no MPC9808 detected ... Check your wiring!");
    while(1);
  }
  Serial.println("All Ok");
  delay(1000); // Wait for sensor stabilization
}

void loop()
{
  tcaselect(0);
  float c1 = tempsensor1.readTempC();
  Serial.print("Temp1: "); 
  Serial.println(c1);

  tcaselect(1);
  float c2 = tempsensor2.readTempC();
  Serial.print("Temp2: "); 
  Serial.println(c2, 4);

  Serial.println("------------------------------");
  delay(500);
}

void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}