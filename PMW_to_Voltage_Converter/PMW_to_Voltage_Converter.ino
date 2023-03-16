/*
Author - Chandan Sinha
Date - March 14, 2023

*Use* - Replaces the potentiometer in Motor-VFD connection to vary the frequency output (and hence the RPM) of the motor.

We convert the PWM output of the arduino to analog voltage output (ideally 0-10V) using PWM-to-Voltage
converter. The actual output caps at 8.6V at 100% duty cycle of 2 kHz PWM signal. 

*Testing* - We first calibrated it 50% duty cycle of the 980 Hz PWM output from Arduino Mega pin 4. The potentiometer
was adjusted to give 5V output. Then we increased the duty cycle to 100% but the output did not increase beyond 8.6V
for both the units. 
*/

const int pwmPin = 9; // PWM pin to use
const int pwmFrequency = 2000; // PWM frequency in Hz

void setup() {
  pinMode(pwmPin, OUTPUT); // set the PWM pin as an output
  // set the PWM frequency to 2 kHz
  TCCR1B = (TCCR1B & 0b11111000) | (0x01 & 0x07);
}

void loop() {
  // set the PWM duty cycle to 50%
  analogWrite(pwmPin, 255);
  delay(1000); // wait for 1 second
}
