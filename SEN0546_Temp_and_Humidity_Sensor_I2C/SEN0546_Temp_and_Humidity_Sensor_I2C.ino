/*
Code to read the output of SEN0546 Temperature and Humidity Sensor using I2C connection. 
Yellow - SDA
White - SCL
*/

#include <Wire.h>

#define address1 0x40 // SEN0546

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
  Serial.println("All ok");
  delay(1000);
}

void loop()
{
  readReg(0x00, buf, 4, address1);
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