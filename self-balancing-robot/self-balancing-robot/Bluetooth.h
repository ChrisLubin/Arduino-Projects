#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

CONTROL_MODE controlMode = MANUAL;

void setUpBluetooth() {
  Dabble.begin(9600, 0, 1);
  Dabble.pin_rx = 0;
  Dabble.pin_tx = 1;
}

void bluetoothLoop() {
  Dabble.processInput();
}

void waitUntilNot(bool (*funcToCheck)()) {
  while((*funcToCheck)()) {
    delay(1);
    Dabble.processInput();
  }
}

MOTOR_ACTIONS getActionFromBluetooth() {
  if (GamePad.isTrianglePressed()) {
    waitUntilNot([]() { return GamePad.isTrianglePressed(); });

    return INCREASE_SPEED;
  } else if (GamePad.isCrossPressed()) {
    waitUntilNot([]() { return GamePad.isCrossPressed(); });

    return DECREASE_SPEED;
  } else if (GamePad.isUpPressed()) {
    return GO_FORWARD;
  } else if (GamePad.isRightPressed()) {
    return ROTATE_RIGHT_IN_PLACE;
  } else if (GamePad.isCirclePressed()) {
    return ROTATE_RIGHT_IN_CIRCLE;
  } else if (GamePad.isDownPressed()) {
    return GO_BACKWARD;
  } else if (GamePad.isLeftPressed()) {
    return ROTATE_LEFT_IN_PLACE;
  } else if (GamePad.isSquarePressed()) {
    return ROTATE_LEFT_IN_CIRCLE;
  }

  return NONE;
}

CONTROL_MODE getControlModeFromBluetooth() {
  if (GamePad.isStartPressed()) {
    controlMode = controlMode == MANUAL ? SELF_BALANCING : MANUAL;

    waitUntilNot([]() { return GamePad.isStartPressed(); });
  }

  return controlMode;
}
