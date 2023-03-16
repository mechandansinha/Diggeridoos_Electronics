/*
Author - Chandan Sinha
Date - March 14, 2023

https://wiki.dfrobot.com/Analog_Gas_Sensor_MQ4___SKU_SEN0129_#target_2

Code for reading the Gas sensor. 

NEED TO BE CALIBRATED FOR METHANE. 

----------------------------------------
SENSITVITY ADJUSTMENT

Resistance value of MQ-4 is difference to various kinds and various concentration gases. 
So,When using this components, sensitivity adjustment is very necessary. we recommend that you 
calibrate the detector for 5000ppm of CH4 concentration in air and use value of Load resistance ( RL) 
about 20KΩ(10KΩ to 47KΩ). When accurately measuring, the proper alarm point for the gas detector should 
be determined after considering the temperature and humidity influence.
*/

void setup()
{
  Serial.begin(9600); //Set serial baud rate to 9600 bps
}
void loop()
{
int val;
val=analogRead(0);Read Gas value from analog 0
Serial.println(val,DEC);//Print the value to serial port
delay(100);
}