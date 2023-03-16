int solenoid_pin = 24;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(solenoid_pin, OUTPUT);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(solenoid_pin, HIGH);
  delay(5000);
  digitalWrite(solenoid_pin, LOW);
  delay(5000);
}
