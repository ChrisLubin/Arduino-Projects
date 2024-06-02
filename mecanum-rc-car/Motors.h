#define LOWEST_MOTOR_SPEED 130
#define HIGHEST_MOTOR_SPEED 255
#define DEFAULT_MOTOR_SPEED 150
#define MOTOR_SPEED_CHANGE_INTERVAL 15

int motorSpeed = DEFAULT_MOTOR_SPEED;

void stopAll() {
  analogWrite(MOTOR_1_ENABLE_PIN, 0);
  analogWrite(MOTOR_2_ENABLE_PIN, 0);
  analogWrite(MOTOR_3_ENABLE_PIN, 0);
  analogWrite(MOTOR_4_ENABLE_PIN, 0);
}

void setUpMotors() {
  pinMode(MOTOR_1_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_1_IN_1_PIN, OUTPUT);
  pinMode(MOTOR_1_IN_2_PIN, OUTPUT);
  pinMode(MOTOR_2_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_2_IN_1_PIN, OUTPUT);
  pinMode(MOTOR_2_IN_2_PIN, OUTPUT);
  pinMode(MOTOR_3_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_3_IN_1_PIN, OUTPUT);
  pinMode(MOTOR_3_IN_2_PIN, OUTPUT);
  pinMode(MOTOR_4_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_4_IN_1_PIN, OUTPUT);
  pinMode(MOTOR_4_IN_2_PIN, OUTPUT);
  stopAll();
}

void rotateMotor1(bool isForward) {
  analogWrite(MOTOR_1_ENABLE_PIN, motorSpeed);
  digitalWrite(MOTOR_1_IN_1_PIN, isForward ? HIGH : LOW);
  digitalWrite(MOTOR_1_IN_2_PIN, isForward ? LOW : HIGH);
}

void rotateMotor2(bool isForward) {
  analogWrite(MOTOR_2_ENABLE_PIN, motorSpeed);
  digitalWrite(MOTOR_2_IN_1_PIN, isForward ? HIGH : LOW);
  digitalWrite(MOTOR_2_IN_2_PIN, isForward ? LOW : HIGH);
}

void rotateMotor3(bool isForward) {
  analogWrite(MOTOR_3_ENABLE_PIN, motorSpeed);
  digitalWrite(MOTOR_3_IN_1_PIN, isForward ? HIGH : LOW);
  digitalWrite(MOTOR_3_IN_2_PIN, isForward ? LOW : HIGH);
}

void rotateMotor4(bool isForward) {
  analogWrite(MOTOR_4_ENABLE_PIN, motorSpeed);
  digitalWrite(MOTOR_4_IN_1_PIN, isForward ? HIGH : LOW);
  digitalWrite(MOTOR_4_IN_2_PIN, isForward ? LOW : HIGH);
}

void goForward() {
  rotateMotor1(true);
  rotateMotor2(true);
  rotateMotor3(true);
  rotateMotor4(true);
}

void goRight() {
  rotateMotor1(true);
  rotateMotor2(false);
  rotateMotor3(false);
  rotateMotor4(true);
}

void goBack() {
  rotateMotor1(false);
  rotateMotor2(false);
  rotateMotor3(false);
  rotateMotor4(false);
}

void goLeft() {
  rotateMotor1(false);
  rotateMotor2(true);
  rotateMotor3(true);
  rotateMotor4(false);
}

void rotateRight() {
  rotateMotor1(true);
  rotateMotor2(false);
  rotateMotor3(true);
  rotateMotor4(false);
}

void rotateLeft() {
  rotateMotor1(false);
  rotateMotor2(true);
  rotateMotor3(false);
  rotateMotor4(true);
}

void goForwardDiagonal(bool isRight) {
  if (isRight) {
    rotateMotor1(true);
    analogWrite(MOTOR_2_ENABLE_PIN, 0);
    analogWrite(MOTOR_3_ENABLE_PIN, 0);
    rotateMotor4(true);
  } else {
    analogWrite(MOTOR_1_ENABLE_PIN, 0);
    rotateMotor2(true);
    rotateMotor3(true);
    analogWrite(MOTOR_4_ENABLE_PIN, 0);
  }
}

void goBackwardDiagonal(bool isRight) {
  if (isRight) {
    analogWrite(MOTOR_1_ENABLE_PIN, 0);
    rotateMotor2(false);
    rotateMotor3(false);
    analogWrite(MOTOR_4_ENABLE_PIN, 0);
  } else {
    rotateMotor1(false);
    analogWrite(MOTOR_2_ENABLE_PIN, 0);
    analogWrite(MOTOR_3_ENABLE_PIN, 0);
    rotateMotor4(false);
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
    case GO_FORWARD:
      goForward();
      break;
    case GO_RIGHT:
      goRight();
      break;
    case GO_BACKWARD:
      goBack();
      break;
    case GO_LEFT:
      goLeft();
      break;
    case ROTATE_LEFT:
      rotateLeft();
      break;
    case ROTATE_RIGHT:
      rotateRight();
      break;
    case INCREASE_SPEED:
      increaseSpeed();
      break;
    case DECREASE_SPEED:
      decreaseSpeed();
      break;
    default:
      stopAll();
      break;
  }
}