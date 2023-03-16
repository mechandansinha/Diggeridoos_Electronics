/******************************************************************************
SparkFun Multiplexer Analog Input Test

Author - Chandan Sinha
Date - March 3, 2023

We read two pressure transducers connected to 8 channel 74HC4051 analog
multiplexer/demultiplexer using a single ADC channel and Arduino Mega.

Hardware Hookup:
Mux Breakout ----------- Arduino
  S0 ------------------- 2
  S1 ------------------- 3
  S2 ------------------- 4
  Z -------------------- A0
VCC ------------------- 5V
GND ------------------- GND
(VEE should be connected to GND)

The multiplexers independent I/O (Y0-Y7) can each be wired
to analog signal-producing component.

******************************************************************************/

// Pin Definitions //
const int selectPins[3] = {2, 3, 4}; // S0~2, S1~3, S2~4

const int zInput = A0; // Connect common (Z) to A0 (analog input)

void setup() 
{
  Serial.begin(9600);

  // Set up the select pins as outputs:
  for (int i=0; i<3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }

  pinMode(zInput, INPUT); // Set up Z as an input

  // Print the header:
  // Serial.println("Y0\tY1\tY2\tY3\tY4\tY5\tY6\tY7");
  // Serial.println("---\t---\t---\t---\t---\t---\t---\t---");
  Serial.println("Y0\tY1");
  Serial.println("---\t---");
}

void loop() 
{
  // Loop through all eight pins.
  for (byte pin=0; pin<=1; pin++)
  {
    selectMuxPin(pin); // Select one at a time
    int inputValue = analogRead(zInput); // and read Z
    Serial.print(String(inputValue) + "\t");
  }
  Serial.println();
  delay(500);
}

// The selectMuxPin function sets the S0, S1, and S2 pins
// accordingly, given a pin from 0-7.
void selectMuxPin(byte pin)
{
  for (int i=0; i<3; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}
