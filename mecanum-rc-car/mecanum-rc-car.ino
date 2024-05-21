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
#define MOTOR_SPEED 150

// For testing BT inputs
String lastAction = "None";

#define ULTRA_SONIC_ECHO_PIN A2
#define ULTRA_SONIC_TRIG_PIN A3

#define PROPER_DISTANCE_CHECK_COUNT 5 // How many valid distance checks do we need to update actualDistance
#define DISTANCE_DIFF_THRESHOLD 7 // The acceptable max difference between valid checks
#define AUTONOMOUS_MODE_TOO_CLOSE_DISTANCE 20
long actualDistance = 0;
long mostRecentDistances[PROPER_DISTANCE_CHECK_COUNT] = { -1, -1, -1, -1, -1 };
bool isInAutonomousMode = false;

// For testing autonomous mode
bool isTestingAutonomousMode = false;

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

  pinMode(ULTRA_SONIC_ECHO_PIN, INPUT);
  pinMode(ULTRA_SONIC_TRIG_PIN, OUTPUT);
}

void loop() {
  delay(5);
  Dabble.processInput();

  if (isTestingAutonomousMode) {
    updateMostRecentDistances();
    return;
  }

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

  if (GamePad.isStartPressed()) {
    lastAction = "Pressed start!";
    Serial.println(lastAction);
    toggleAutonomousMode();

    delay(150); // Add delay so switching is only registered once
  }

  if (isInAutonomousMode) {
    updateMostRecentDistances();

    if (actualDistance == 0) {
      // Allow distance to be calculated before moving for the first time
      return;
    } else if (actualDistance <= AUTONOMOUS_MODE_TOO_CLOSE_DISTANCE) {
      rotateRight();
    } else {
      goForward();
    }

    return;
  }

  if (GamePad.isUpPressed()) {
    lastAction = "Pressed up!";
    Serial.println(lastAction);
    goForward();
  } else if (GamePad.isRightPressed()) {
    lastAction = "Pressed right!";
    Serial.println(lastAction);
    goRight();
  } else if (GamePad.isDownPressed()) {
    lastAction = "Pressed down!";
    Serial.println(lastAction);
    goBack();
  } else if (GamePad.isLeftPressed()) {
    lastAction = "Pressed left!";
    Serial.println(lastAction);
    goLeft();
  } else if (GamePad.isCirclePressed()) {
    lastAction = "Pressed Circle!";
    Serial.println(lastAction);
    rotateRight();
  } else if (GamePad.isSquarePressed()) {
    lastAction = "Pressed Square!";
    Serial.println(lastAction);
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

long getUltraSonicSensorDistance() {
  digitalWrite(ULTRA_SONIC_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRA_SONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_SONIC_TRIG_PIN, LOW);

  long duration = pulseIn(ULTRA_SONIC_ECHO_PIN, HIGH);
  long centimeters = duration / 29 / 2;
  return centimeters;
}

void updateMostRecentDistances() {
  if (isTestingAutonomousMode) {
    logDistances();
  }

  long currentDistance = getUltraSonicSensorDistance();
  Serial.print("Calculated now - ");
  Serial.println(currentDistance);
  bool shouldResetArray = false;

  for (int i = 0; i < PROPER_DISTANCE_CHECK_COUNT; i++) {
    long distanceInArray = mostRecentDistances[i];

    if (i == PROPER_DISTANCE_CHECK_COUNT - 1 && distanceInArray != -1) {
      // Got all valid distances in a row
      actualDistance = currentDistance;
      shouldResetArray = true;
      break;
    }

    if (distanceInArray != -1 && abs(currentDistance - distanceInArray) <= DISTANCE_DIFF_THRESHOLD) {
      // Distance is valid
      continue;
    } else if (distanceInArray != -1 && abs(currentDistance - distanceInArray) > DISTANCE_DIFF_THRESHOLD) {
      // Distance is NOT valid
      shouldResetArray = true;
      break;
    } else if (distanceInArray == -1) {
      mostRecentDistances[i] = currentDistance;
      break;
    }
  }

  if (shouldResetArray) {
    for (int i = 0; i < PROPER_DISTANCE_CHECK_COUNT; i++) {
      mostRecentDistances[i] = -1;
    }
  }
}

void logDistances() {
  Serial.print("Actual - ");
  Serial.println(actualDistance);
  Serial.print("Recent Distances - ");

  for (int i = 0; i < PROPER_DISTANCE_CHECK_COUNT; i++) {
    Serial.print(mostRecentDistances[i]);
    Serial.print(", ");
  }

  Serial.println("");
}

void toggleAutonomousMode() {
  isInAutonomousMode = !isInAutonomousMode;

  if (isInAutonomousMode) {
    actualDistance = 0;
    for (int i = 0; i < PROPER_DISTANCE_CHECK_COUNT; i++) {
      mostRecentDistances[i] = -1;
    }
  }
}