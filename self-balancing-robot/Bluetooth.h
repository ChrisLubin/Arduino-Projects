#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define INCLUDE_TERMINAL_MODULE
#include <Dabble.h>

CONTROL_MODE controlMode = SELF_BALANCING;
const int TARGET_ANGLE_OFFSET = 3;
String pidTuningCommand = ""; // Format - {'P' | 'I' | 'D'}{val} (Without curly braces)
const double DEFAULT_DOUBLE_VAL = 0.00;

void setUpBluetooth() {
  Dabble.begin(9600, 0, 1);
  Dabble.pin_rx = 0;
  Dabble.pin_tx = 1;
}

void pidTuningCommandCheckLoop() {
  if (!Terminal.available()) {
    return;
  }
  
  String command = Terminal.readString();
  String firstLetter = command.substring(0, 1);
  double pidTuningVal = command.substring(1).toDouble();

  if ((firstLetter != "P" && firstLetter != "I" && firstLetter != "D") || pidTuningVal == DEFAULT_DOUBLE_VAL) {
    return;
  }

  pidTuningCommand = command;
}

void bluetoothLoop() {
  Dabble.processInput();

  pidTuningCommandCheckLoop();
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

// Used to move bot forward or backward
int getTargetAngleOffsetFromBluetooth() {
  if (GamePad.isUpPressed()) {
    return TARGET_ANGLE_OFFSET;
  } else if (GamePad.isDownPressed()) {
    return -TARGET_ANGLE_OFFSET;
  } else {
    return 0;
  }
}

bool hasPidCommandFromBluetooth(PID_TUNINGS parameter) {
  String firstLetter = pidTuningCommand.substring(0, 1);

  switch(parameter) {
    case P:
      return firstLetter == "P";
    case I:
      return firstLetter == "I";
    case D:
      return firstLetter == "D";
    default:
      return false;
  }

  return false;
}

double getPidCommandValFromBluetooth(PID_TUNINGS parameter) {
  if (!hasPidCommandFromBluetooth(parameter)) {
    return DO_NOT_CHANGE_PID_VAL;
  }

  double tuningVal = pidTuningCommand.substring(1).toDouble();
  pidTuningCommand = "";
  return tuningVal;
}
