#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

CONTROL_MODE controlMode = SELF_BALANCING;

void setUpBluetooth() {
  Dabble.begin(9600, 0, 1);
  Dabble.pin_rx = 0;
  Dabble.pin_tx = 1;
}

void bluetoothLoop() {
  Dabble.processInput();
}

void waitUntil(bool (*funcToCheck)()) {
  while(!(*funcToCheck)()) {
    delay(1);
    Dabble.processInput();
  }
}

MotorCommand getCommandFromBluetooth() {
  MotorCommand command;

  if (GamePad.isTrianglePressed()) {
    waitUntil([]() { return !GamePad.isTrianglePressed(); });

    command.action = INCREASE_SPEED;
  } else if (GamePad.isCrossPressed()) {
    waitUntil([]() { return !GamePad.isCrossPressed(); });

    command.action = DECREASE_SPEED;
  } else if (GamePad.isUpPressed()) {
    command.action = GO_FORWARD;
    command.speed = DONT_CHANGE_SPEED_VALUE;
  } else if (GamePad.isRightPressed()) {
    command.action = ROTATE_RIGHT_IN_PLACE;
    command.speed = DONT_CHANGE_SPEED_VALUE;
  } else if (GamePad.isCirclePressed()) {
    command.action = ROTATE_RIGHT_IN_CIRCLE;
    command.speed = DONT_CHANGE_SPEED_VALUE;
  } else if (GamePad.isDownPressed()) {
    command.action = GO_BACKWARD;
    command.speed = DONT_CHANGE_SPEED_VALUE;
  } else if (GamePad.isLeftPressed()) {
    command.action = ROTATE_LEFT_IN_PLACE;
    command.speed = DONT_CHANGE_SPEED_VALUE;
  } else if (GamePad.isSquarePressed()) {
    command.action = ROTATE_LEFT_IN_CIRCLE;
    command.speed = DONT_CHANGE_SPEED_VALUE;
  } else {
    command.action = NONE;
  }

  return command;
}

CONTROL_MODE getControlModeFromBluetooth() {
  if (GamePad.isStartPressed()) {
    controlMode = controlMode == MANUAL ? SELF_BALANCING : MANUAL;

    waitUntil([]() { return !GamePad.isStartPressed(); });
  }

  return controlMode;
}
