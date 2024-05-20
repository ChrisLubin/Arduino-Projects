#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

#define MOTOR_1_ENABLE_PIN 5
#define MOTOR_1_IN_1_PIN 12
#define MOTOR_1_IN_2_PIN 11
#define MOTOR_2_ENABLE_PIN 3
#define MOTOR_2_IN_1_PIN 4
#define MOTOR_2_IN_2_PIN 2
#define MOTOR_3_ENABLE_PIN 6
#define MOTOR_3_IN_1_PIN 13
#define MOTOR_3_IN_2_PIN 7
#define MOTOR_4_ENABLE_PIN 10
#define MOTOR_4_IN_1_PIN 9
#define MOTOR_4_IN_2_PIN 8
#define MOTOR_SPEED 255

// Testing
String lastAction = "None";

void setup() {
  Serial.begin(9600);
  Dabble.begin(9600, A0, A1);
  Dabble.pin_rx = A0;
  Dabble.pin_tx = A1;

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

void loop() {
  delay(50);

  Dabble.processInput();

  // if (GamePad.isLeftPressed() && GamePad.isTrianglePressed()) {
  //   // lastAction = "Pressed up!";
  //   goForwardDiagonal(false);
  // } else if (GamePad.isRightPressed() && GamePad.isTrianglePressed()) {
  //   // lastAction = "Pressed up!";
  //   goForwardDiagonal(true);
  // } else if (GamePad.isLeftPressed() && GamePad.isCrossPressed()) {
  //   // lastAction = "Pressed up!";
  //   goBackwardDiagonal(false);
  // } else if (GamePad.isRightPressed() && GamePad.isCrossPressed()) {
  //   // lastAction = "Pressed up!";
  //   goBackwardDiagonal(true);
  // } else

  if (GamePad.isUpPressed()) {
    lastAction = "Pressed up!";
    goForward();
  } else if (GamePad.isRightPressed()) {
    lastAction = "Pressed right!";
    goRight();
  } else if (GamePad.isDownPressed()) {
    lastAction = "Pressed down!";
    goBack();
  } else if (GamePad.isLeftPressed()) {
    lastAction = "Pressed left!";
    goLeft();
  } else if (GamePad.isCirclePressed()) {
    lastAction = "Pressed Circle!";
    rotateRight();
  } else if (GamePad.isSquarePressed()) {
    lastAction = "Pressed Square!";
    rotateLeft();
  } else {
    stopAll();
  }
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

void stopAll() {
  analogWrite(MOTOR_1_ENABLE_PIN, 0);
  analogWrite(MOTOR_2_ENABLE_PIN, 0);
  analogWrite(MOTOR_3_ENABLE_PIN, 0);
  analogWrite(MOTOR_4_ENABLE_PIN, 0);
}

void rotateMotor1(bool isForward) {
  analogWrite(MOTOR_1_ENABLE_PIN, MOTOR_SPEED);
  digitalWrite(MOTOR_1_IN_1_PIN, isForward ? HIGH : LOW);
  digitalWrite(MOTOR_1_IN_2_PIN, isForward ? LOW : HIGH);
}

void rotateMotor2(bool isForward) {
  analogWrite(MOTOR_2_ENABLE_PIN, MOTOR_SPEED);
  digitalWrite(MOTOR_2_IN_1_PIN, isForward ? HIGH : LOW);
  digitalWrite(MOTOR_2_IN_2_PIN, isForward ? LOW : HIGH);
}

void rotateMotor3(bool isForward) {
  analogWrite(MOTOR_3_ENABLE_PIN, MOTOR_SPEED);
  digitalWrite(MOTOR_3_IN_1_PIN, isForward ? HIGH : LOW);
  digitalWrite(MOTOR_3_IN_2_PIN, isForward ? LOW : HIGH);
}

void rotateMotor4(bool isForward) {
  analogWrite(MOTOR_4_ENABLE_PIN, MOTOR_SPEED);
  digitalWrite(MOTOR_4_IN_1_PIN, isForward ? HIGH : LOW);
  digitalWrite(MOTOR_4_IN_2_PIN, isForward ? LOW : HIGH);
}