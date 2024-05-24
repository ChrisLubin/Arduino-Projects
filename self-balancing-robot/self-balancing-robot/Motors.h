#define MOTOR_SPEED 50

void stopMotors()
{
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(STBY_PIN, HIGH);
  analogWrite(PWMA_LEFT, 0);
  analogWrite(PWMB_RIGHT, 0);
}

void setUpMotors() {
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(PWMA_LEFT, OUTPUT);
  pinMode(PWMB_RIGHT, OUTPUT);
  pinMode(STBY_PIN, OUTPUT);

  stopMotors();
}

void rotateMotorsForward()
{
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(STBY_PIN, HIGH);
  analogWrite(PWMA_LEFT, MOTOR_SPEED);
  analogWrite(PWMB_RIGHT, MOTOR_SPEED);
}

void rotateMotorsBackwards()
{
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(STBY_PIN, HIGH);
  analogWrite(PWMA_LEFT, MOTOR_SPEED);
  analogWrite(PWMB_RIGHT, MOTOR_SPEED);
}

void processMotorAction(MOTOR_ACTIONS action) {
  switch(action) {
    case GO_FORWARD:
      rotateMotorsForward();
      break;
    case GO_BACKWARD:
      rotateMotorsBackwards();
      break;
    default:
      stopMotors();
      break;
  }
}
