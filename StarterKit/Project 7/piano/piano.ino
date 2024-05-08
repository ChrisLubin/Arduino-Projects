const int switchPin = 2;
const int motorPin = 9;
int switchState = 0;

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  switchState = digitalRead(switchPin);
  digitalWrite(motorPin, switchState);
}