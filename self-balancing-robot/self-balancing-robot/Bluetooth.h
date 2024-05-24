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

MOTOR_ACTIONS getActionFromBluetooth() {
  if (GamePad.isUpPressed()) {
    return GO_FORWARD;
  } else if (GamePad.isRightPressed()) {
    return ROTATE_RIGHT;
  } else if (GamePad.isDownPressed()) {
    return GO_BACKWARD;
  } else if (GamePad.isLeftPressed()) {
    return ROTATE_LEFT;
  }

  return NONE;
}

CONTROL_MODE getControlModeFromBluetooth() {
  if (GamePad.isStartPressed()) {
    controlMode = controlMode == MANUAL ? SELF_BALANCING : MANUAL;
    delay(150);
  }

  return controlMode;
}