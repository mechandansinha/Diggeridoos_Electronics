/*
Author - Chandan Sinha
Date - February 26, 2023
Reading 2 Adafruit MCP9808 temperature sensor and 1 DFROBOT SEN0546 Temperature and Humidity Sensor
using Adafruit TCA9548A I2C multiplexer connected on ports 0, 1, and 2 respectively.
*/

#include <Wire.h>
#include "Adafruit_MCP9808.h"

#define TCAADDR 0x70
#define SENSOR1_ADDRESS 0x18
#define SENSOR2_ADDRESS 0x19
#define address 0x40 // SEN0546

Adafruit_MCP9808 tempsensor1 = Adafruit_MCP9808();
Adafruit_MCP9808 tempsensor2 = Adafruit_MCP9808();

//SEN0546
char dtaUart[15];
char dtaLen = 0;
uint8_t Data[100] = {0};
uint8_t buff[100] = {0};

uint8_t buf[4] = {0};
uint16_t data, data1;
float temp;
float hum;

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
  Serial.println("All ok");
  delay(1000);
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
  
  tcaselect(2);
  readReg(0x00, buf, 4);
  data = buf[0] << 8 | buf[1];
  data1 = buf[2] << 8 | buf[3];
  temp = ((float)data * 165 / 65535.0) - 40.0;
  hum =  ((float)data1 / 65535.0) * 100;
  Serial.print("temp(C):");
  Serial.print(temp);
  Serial.print("\t");
  Serial.print("hum(%RH):");
  Serial.println(hum);

  Serial.println("------------------------------");
  delay(500);
}

void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

uint8_t readReg(uint8_t reg, const void* pBuf, size_t size)
{
  if (pBuf == NULL) {
    Serial.println("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  Wire.beginTransmission(address);
  Wire.write(&reg, 1);
  if ( Wire.endTransmission() != 0) {
    return 0;
  }
  delay(20);
  Wire.requestFrom(address, (uint8_t) size);
  for (uint16_t i = 0; i < size; i++) {
    _pBuf[i] = Wire.read();
  }
  return size;
}