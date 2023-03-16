/*
Date - 02/27/2023
Author - Chandan Sinha

Arduino Mega transmits the data using MCP2515 CAN Controller module to Arduino Due. Contrary to Due,
Arduino Mega has dedicated GPIO pins for SPI connection, so we don't necessarily need to use
ICSP header. The pin connections are as follows - 
Refer this document for pin numbers - https://content.arduino.cc/assets/Pinout-Mega2560rev3_latest.pdf

  |   MCP2515     | Arduino Mega 2560 Rev3 |
  ------------------------------------------
  |     VCC       |         5V             |
  |     GND       |         GND            |
  |     CS        |         10             |
  | SO/MISO/CIPO  |         50             |
  | SI/MOSI/COPI  |         51             |
  |     SCK       |         52             |
  |     INT       |         2              |
  ------------------------------------------
*/

#include <SPI.h>
#include <Wire.h>
#include "mcp2515_can.h"

const int SPI_CS_PIN = 10; // Chip/Slave Select (CS/SS) pin
const int CAN_INT_PIN = 2; // Interrup pin

mcp2515_can CAN(SPI_CS_PIN); // Set CS pin

//SEN0546 - Temperature and Humidity Sensor
#define address1 0x40
char dtaUart[15];
char dtaLen = 0;
uint8_t Data[100] = {0};
uint8_t buff[100] = {0};

uint8_t buf[4] = {0};
uint16_t data, data1;
// float temp;
// float hum;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  while(!Serial){};
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
      Serial.println("CAN init fail, retry...");
      delay(100);
  }
  Serial.println("CAN init ok!");
}

// unsigned char stmp[8] = {0, 0x2F, 2, 3, 4, 5, 6, 7};

// Define union for temp data
union{
  float f;
  byte b[4];
} temp;

// union hum{
//   float f;
//   byte b[2];
// }

void loop() {
  readReg(0x00, buf, 4, address1);
  data = buf[0] << 8 | buf[1];
  data1 = buf[2] << 8 | buf[3];
  temp.f = ((float)data * 165 / 65535.0) - 40.0;
  // hum.f =  ((float)data1 / 65535.0) * 100;
  // stmp = temp.b;
  
  // send data:  id = 0x00, standrad frame, data len = 4, stmp: data buf
  CAN.sendMsgBuf(0x3F, 0, 4, temp.b);
  delay(100);                       // send data per 100ms
  Serial.println(temp.f);
  Serial.println("CAN BUS sendMsgBuf ok!");
  Serial.println("------------------");
}

// Function to read SEN0546 Temperature and Humidity Sensor
uint8_t readReg(uint8_t reg, const void* pBuf, size_t size, uint8_t address)
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
