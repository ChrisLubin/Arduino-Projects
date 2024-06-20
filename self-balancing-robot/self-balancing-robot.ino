#include "Helpers.h"
#include "Actions.h"
#include "Pins.h"
#include "Motors.h"
#include "Bluetooth.h"
#include "Leds.h"
#include "Accelerometer.h"

void setup() {
  Serial.begin(9600);

  setUpMotors();
  setUpBluetooth();
  setUpLeds();
  setUpAccelerometer();
}

void loop() {
  delay(2);

  bluetoothLoop();
  checkAndUpdatePidTuning();

  accelerometerLoop();
  getAndProcessMotorCommand();

  updateLedColors();
}

void getAndProcessMotorCommand() {
  MotorCommand command;
  CONTROL_MODE controlMode = getControlModeFromBluetooth();

  switch(controlMode) {
    case MANUAL:
      command = getCommandFromBluetooth();
      break;
    case SELF_BALANCING:
      double targetAngleOffset = getTargetAngleOffsetFromBluetooth();
      setAccelerometerTargetAngleOffset(targetAngleOffset);
      command = getCommandFromAccelerometer();
      break;
    default:
      command.action = NONE;
      command.speed = 0;
      break;
  }

  processMotorCommand(command);
}

// Checks if any command received from bluetooth to update PID tuning
void checkAndUpdatePidTuning() {
  if (hasPidCommandFromBluetooth(P)) {
    setAccelerometerTuningVal(P, getPidCommandValFromBluetooth(P));
  } else if (hasPidCommandFromBluetooth(I)) {
    setAccelerometerTuningVal(I, getPidCommandValFromBluetooth(I));
  } else if (hasPidCommandFromBluetooth(D)) {
    setAccelerometerTuningVal(D, getPidCommandValFromBluetooth(D));
  }
}

void updateLedColors() {
  int r = constrain(map(abs(getAccelerometerAngleDiff()), 0, 20, 0, 255), 0, 255);
  int g = constrain(map(abs(getAccelerometerAngleDiff()), 0, 20, 255, 0), 0, 255);
  int b = 0;

  ledsLoop(r, g, b);
}