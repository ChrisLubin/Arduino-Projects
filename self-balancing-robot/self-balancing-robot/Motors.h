#define MOTOR_SPEED 50

void stopMotors()
{
  digitalWrite(STBY_PIN, LOW);
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

void moveLeftWheel(bool isForward) {
  digitalWrite(STBY_PIN, HIGH);
  digitalWrite(AIN1, isForward ? LOW : HIGH);
  analogWrite(PWMA_LEFT, MOTOR_SPEED);
}

void moveRightWheel(bool isForward) {
  digitalWrite(STBY_PIN, HIGH);
  digitalWrite(BIN1, isForward ? LOW : HIGH);
  analogWrite(PWMB_RIGHT, MOTOR_SPEED);
}

void moveForward()
{
  moveLeftWheel(true);
  moveRightWheel(true);
}

void moveBackwards()
{
  moveLeftWheel(false);
  moveRightWheel(false);
}

void rotateRight()
{
  moveLeftWheel(true);
  moveRightWheel(false);
}

void rotateLeft()
{
  moveLeftWheel(false);
  moveRightWheel(true);
}

void processMotorAction(MOTOR_ACTIONS action) {
  switch(action) {
    case GO_FORWARD:
      moveForward();
      break;
    case ROTATE_RIGHT:
      rotateRight();
      break;
    case GO_BACKWARD:
      moveBackwards();
      break;
    case ROTATE_LEFT:
      rotateLeft();
      break;
    default:
      stopMotors();
      break;
  }
}
