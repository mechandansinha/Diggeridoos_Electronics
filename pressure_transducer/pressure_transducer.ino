#include <math.h>

#define press_trans A0

float pressure = 301.35;
float voltage = 1.12568;
int sensorVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(press_trans, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorVal = analogRead(press_trans);
  pressure = sensorVal*(3000/1024);
  voltage = sensorVal/256;
  Serial.print("Sensor value: ");
  Serial.println(sensorVal);
  Serial.print("Pressure (psi): ");
  printDouble(pressure, 5);
  Serial.print("Voltage (V): ");
  printDouble(voltage, 5);
  Serial.println("---------------------");
  delay(500);
}

void printDouble( double val, unsigned int precision){
// prints val with number of decimal places determine by precision
// NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
// example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)

    Serial.print (int(val));  //prints the int part
    Serial.print("."); // print the decimal point
    unsigned int frac;
    if(val >= 0)
        frac = (val - int(val)) * precision;
    else
        frac = (int(val)- val ) * precision;
    Serial.println(frac,DEC) ;
} 
