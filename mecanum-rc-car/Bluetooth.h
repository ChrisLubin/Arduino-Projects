#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

CONTROL_MODE controlMode = MANUAL;
auto isStartNotPressed = [&GamePad]() { return !GamePad.isStartPressed(); };
auto isTriangleNotPressed = [&GamePad]() { return !GamePad.isTrianglePressed(); };
auto isCrossNotPressed = [&GamePad]() { return !GamePad.isCrossPressed(); };

enum BUTTONS_FOR_WAIT {
  START,
  TRIANGLE,
  CROSS
};

void setUpBluetooth() {
  Dabble.begin(9600, A0, A1);
  Dabble.pin_rx = A0;
  Dabble.pin_tx = A1;
}

void bluetoothLoop() {
  Dabble.processInput();
}

void waitUntilButtonNotPressed(BUTTONS_FOR_WAIT button) {
  auto loopFunc = []() {
    delay(1);
    Dabble.processInput();
  };

  switch (button) {
    case START:
      waitUntil(isStartNotPressed, loopFunc);
      break;
    case TRIANGLE:
      waitUntil(isTriangleNotPressed, loopFunc);
      break;
    case CROSS:
      waitUntil(isCrossNotPressed, loopFunc);
      break;
    default:
      break;
  }
}

MOTOR_ACTIONS getMotorActionFromBluetooth() {
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
    Serial.println("Pressed up!");
    return GO_FORWARD;
  } else if (GamePad.isRightPressed()) {
    Serial.println("Pressed right!");
    return GO_RIGHT;
  } else if (GamePad.isDownPressed()) {
    Serial.println("Pressed down!");
    return GO_BACKWARD;
  } else if (GamePad.isLeftPressed()) {
    Serial.println("Pressed left!");
    return GO_LEFT;
  } else if (GamePad.isCirclePressed()) {
    Serial.println("Pressed Circle!");
    return ROTATE_RIGHT;
  } else if (GamePad.isSquarePressed()) {
    Serial.println("Pressed Square!");
    return ROTATE_LEFT;
  } else if (GamePad.isTrianglePressed()) {
    Serial.println("Pressed Triangle!");
    waitUntilButtonNotPressed(TRIANGLE);
    return INCREASE_SPEED;
  } else if (GamePad.isCrossPressed()) {
    Serial.println("Pressed X!");
    waitUntilButtonNotPressed(CROSS);
    return DECREASE_SPEED;
  } else {
    return NONE;
  }
}

CONTROL_MODE getControlModeFromBluetooth() {
  if (GamePad.isStartPressed()) {
    controlMode = controlMode == MANUAL ? AUTONOMOUS : MANUAL;
    Serial.println("Pressed Start!");
    waitUntilButtonNotPressed(START);
  }

  return controlMode;
}
