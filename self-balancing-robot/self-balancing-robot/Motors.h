#define LOWEST_MOTOR_SPEED 50
#define HIGHEST_MOTOR_SPEED 255
#define DEFAULT_MOTOR_SPEED 50
#define MOTOR_SPEED_CHANGE_INTERVAL 15

int motorSpeed = DEFAULT_MOTOR_SPEED;

void stopMotors()
{
  digitalWrite(STBY_PIN, LOW);
  analogWrite(PWMA_LEFT, 0);
  analogWrite(PWMB_RIGHT, 0);
}

void stopLeftWheel() {
  analogWrite(PWMA_LEFT, 0);
}

void stopRightWheel() {
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
  analogWrite(PWMA_LEFT, motorSpeed);
}

void moveRightWheel(bool isForward) {
  digitalWrite(STBY_PIN, HIGH);
  digitalWrite(BIN1, isForward ? LOW : HIGH);
  analogWrite(PWMB_RIGHT, motorSpeed);
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

void rotateRight(bool isInPlace)
{
  moveLeftWheel(true);

  if (isInPlace) {
    moveRightWheel(false);
  } else {
    stopRightWheel();
  }
}

void rotateLeft(bool isInPlace)
{
  moveRightWheel(true);

  if (isInPlace) {
    moveLeftWheel(false);
  } else {
    stopLeftWheel();
  }
}

void increaseSpeed() {
  motorSpeed = constrain(motorSpeed + MOTOR_SPEED_CHANGE_INTERVAL, LOWEST_MOTOR_SPEED, HIGHEST_MOTOR_SPEED);
}

void decreaseSpeed() {
  motorSpeed = constrain(motorSpeed - MOTOR_SPEED_CHANGE_INTERVAL, LOWEST_MOTOR_SPEED, HIGHEST_MOTOR_SPEED);
}

void processMotorAction(MOTOR_ACTIONS action) {
  switch(action) {
    case INCREASE_SPEED:
      increaseSpeed();
      break;
    case DECREASE_SPEED:
      decreaseSpeed();
      break;
    case GO_FORWARD:
      moveForward();
      break;
    case ROTATE_RIGHT_IN_PLACE:
      rotateRight(true);
      break;
    case ROTATE_RIGHT_IN_CIRCLE:
      rotateRight(false);
      break;
    case GO_BACKWARD:
      moveBackwards();
      break;
    case ROTATE_LEFT_IN_PLACE:
      rotateLeft(true);
      break;
    case ROTATE_LEFT_IN_CIRCLE:
      rotateLeft(false);
      break;
    default:
      stopMotors();
      break;
  }
}
