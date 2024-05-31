#define LOWEST_MOTOR_SPEED 50
#define HIGHEST_MOTOR_SPEED 255
#define DEFAULT_MOTOR_SPEED 50
#define MOTOR_SPEED_CHANGE_INTERVAL 15

int motorSpeed = DEFAULT_MOTOR_SPEED;
// volatile long motorEncoder = 0;

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

// void onLeftChange() {
//   motorEncoder++;
// }

void setUpMotors() {
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(PWMA_LEFT, OUTPUT);
  pinMode(PWMB_RIGHT, OUTPUT);
  pinMode(STBY_PIN, OUTPUT);

  // attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A_PIN), onLeftChange, CHANGE);

  stopMotors();
}

int getProperSpeed(int speed) {
  if (speed == DONT_CHANGE_SPEED_VALUE) {
    return motorSpeed;
  }

  return speed;
}

void moveLeftWheel(bool isForward, int speed) {
  digitalWrite(STBY_PIN, HIGH);
  digitalWrite(AIN1, isForward ? LOW : HIGH);
  analogWrite(PWMA_LEFT, getProperSpeed(speed));
}

void moveRightWheel(bool isForward, int speed) {
  digitalWrite(STBY_PIN, HIGH);
  digitalWrite(BIN1, isForward ? LOW : HIGH);
  analogWrite(PWMB_RIGHT, getProperSpeed(speed));
}

void moveForward(int speed)
{
  moveLeftWheel(true, speed);
  moveRightWheel(true, speed);
}

void moveBackwards(int speed)
{
  moveLeftWheel(false, speed);
  moveRightWheel(false, speed);
}

void rotateRight(bool isInPlace, int speed)
{
  moveLeftWheel(true, speed);

  if (isInPlace) {
    moveRightWheel(false, speed);
  } else {
    stopRightWheel();
  }
}

void rotateLeft(bool isInPlace, int speed)
{
  moveRightWheel(true, speed);

  if (isInPlace) {
    moveLeftWheel(false, speed);
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

void processMotorCommand(MotorCommand command) {
  switch(command.action) {
    case INCREASE_SPEED:
      increaseSpeed();
      break;
    case DECREASE_SPEED:
      decreaseSpeed();
      break;
    case GO_FORWARD:
      moveForward(command.speed);
      break;
    case ROTATE_RIGHT_IN_PLACE:
      rotateRight(true, command.speed);
      break;
    case ROTATE_RIGHT_IN_CIRCLE:
      rotateRight(false, command.speed);
      break;
    case GO_BACKWARD:
      moveBackwards(command.speed);
      break;
    case ROTATE_LEFT_IN_PLACE:
      rotateLeft(true, command.speed);
      break;
    case ROTATE_LEFT_IN_CIRCLE:
      rotateLeft(false, command.speed);
      break;
    default:
      stopMotors();
      break;
  }
}
