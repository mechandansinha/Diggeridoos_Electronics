// Suggested by ChatGPT
// using MCP2515 CAN controller

/*
Make sure to connect the CANH and CANL pins of the MCP2515 CAN controller on both Arduino Mega and Due. 
Also, both Arduinos should have a common ground connection.
*/

/* ----------- Arduino Mega Code ---------------- */

#include <SPI.h>
#include <mcp_can.h>

// Initialize the MCP2515 CAN controller with CS pin 10
MCP_CAN CAN(10);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize CAN bus at 500kbps
  if(CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN initialization success!");
  } else {
    Serial.println("CAN initialization failed!");
  }
}

void loop() {
  // Send CAN message with ID 0x100 and data {0,1,2,3,4,5,6,7}
  unsigned char data[] = {0,1,2,3,4,5,6,7};
  CAN.sendMsgBuf(0x100, 0, 8, data);

  delay(1000);
}


/* ------------------- Arduino Due Code ------------------ */
#include <SPI.h>
#include <mcp_can.h>

// Initialize the MCP2515 CAN controller with CS pin 9
MCP_CAN CAN(9);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize CAN bus at 500kbps
  if(CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN initialization success!");
  } else {
    Serial.println("CAN initialization failed!");
  }
}

void loop() {
  // Check if there is a CAN message available
  if(CAN.checkReceive() == CAN_MSGAVAIL) {
    // Read the CAN message
    unsigned char len = 0;
    unsigned char buf[8];
    unsigned long id = 0;
    if(CAN.readMsgBuf(&id, &len, buf) == CAN_OK) {
      Serial.print("Received message with ID: ");
      Serial.print(id, HEX);
      Serial.print(" Data: ");
      for(int i=0; i<len; i++) {
        Serial.print(buf[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
  }

  delay(100);
}
