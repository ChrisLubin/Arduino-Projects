const int CONTROL_PIN_1 = 2;
const int CONTROL_PIN_2 = 3;
const int ENABLE_PIN = 9;
const int DIRECTION_PIN = 4;
const int IS_ON_PIN = 5;
const int POT_PIN = A0;

int isOnSwitchVal = 0;
int prevIsOnSwitchVal = 0;
int directionSwitchVal = 0;
int prevDirectionSwitchVal = 0;
int potVal = 0;

int isMotorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 0;

void setup() {
  pinMode(DIRECTION_PIN, INPUT);
  pinMode(IS_ON_PIN, INPUT);
  pinMode(CONTROL_PIN_1, OUTPUT);
  pinMode(CONTROL_PIN_2, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  digitalWrite(ENABLE_PIN, LOW);
}

void loop() {
  isOnSwitchVal = digitalRead(IS_ON_PIN);
  delay(1);
  directionSwitchVal = digitalRead(DIRECTION_PIN);
  potVal = analogRead(POT_PIN);
  motorSpeed = map(potVal, 0, 1023, 0, 255);

  if (isOnSwitchVal != prevIsOnSwitchVal && isOnSwitchVal == HIGH) {
    isMotorEnabled = !isMotorEnabled;
  }
  if (directionSwitchVal != prevDirectionSwitchVal && directionSwitchVal == HIGH) {
    motorDirection = !motorDirection;
  }

  if (motorDirection == 1) {
    digitalWrite(CONTROL_PIN_1, HIGH);
    digitalWrite(CONTROL_PIN_2, LOW);
  } else {
    digitalWrite(CONTROL_PIN_1, LOW);
    digitalWrite(CONTROL_PIN_2, HIGH);
  }
  if (isMotorEnabled == 1) {
    analogWrite(ENABLE_PIN, motorSpeed);
  } else {
    analogWrite(ENABLE_PIN, 0);
  }

  prevIsOnSwitchVal = isOnSwitchVal;
  prevDirectionSwitchVal = directionSwitchVal;
}
