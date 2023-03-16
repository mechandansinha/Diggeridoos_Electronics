#define FWD 50
#define REV 52

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(FWD, OUTPUT);
  pinMode(REV, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(FWD, HIGH);
  delay(2000);
  digitalWrite(FWD, LOW);
  delay(500);
  digitalWrite(REV, HIGH);
  delay(2000);
  digitalWrite(REV, LOW);
  delay(500);
}
