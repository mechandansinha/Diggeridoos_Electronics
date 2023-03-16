#define S_POT_PIN A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // pinMode(S_POT_PIN, INPUT);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(S_POT_PIN);
  Serial.println(val);
  delay(500);
}
