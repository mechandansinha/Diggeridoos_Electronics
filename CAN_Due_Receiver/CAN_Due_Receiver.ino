/*
Date - 02/27/2023
Author - Chandan Sinha

Due receives the data from Arduino Mega using MCP2515 CAN Controller module. Since Due does not have
dedicated GPIO pins for SPI connection, the only way to connect the CAN module to the Due is through 
ICSP header. The pin connections are as follows - 
Refer  this for pin numbers - https://content.arduino.cc/assets/A000056-full-pinout.pdf\

  | MCP2515     | Arduino Due |
  -----------------------------
  |   VCC       |     5V      |
  |   GND       |     GND     |
  |   CS        |     10      |
  |SO/MISO/CIPO |     ICSP 1  |
  |SI/MOSI/COPI |     ICSP 4  |
  |   SCK       |     ICSP 3  |
  |   INT       |     2       |
  -----------------------------
*/

#include <SPI.h>
#include "mcp2515_can.h"

const int SPI_CS_PIN = 10; // Chip/Slave Select (CS/SS) pin
const int CAN_INT_PIN = 2; // Interrup pin

mcp2515_can CAN(SPI_CS_PIN); // Set CS pin                          

void setup() {
  Serial.begin(115200);
  while(!Serial){};
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
      Serial.println("CAN init fail, retry...");
      delay(100);
  }
  Serial.println("CAN init ok!");
}

void loop() {
  unsigned char len = 0;
  unsigned char buf[4];

  if (CAN_MSGAVAIL == CAN.checkReceive()) {         // check if data coming
      CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

      unsigned long canId = CAN.getCanId();

      Serial.println("-----------------------------");
      Serial.print("Get data from ID: 0x");
      Serial.println(canId, HEX);

      for (int i = 0; i < len; i++) { // print the data
          Serial.print(buf[i], HEX);
          Serial.print("\t");
      }
      Serial.println();
  }
}
