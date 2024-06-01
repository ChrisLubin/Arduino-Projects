#include "Actions.h"
#include "Pins.h"
#include "Motors.h"
#include "Bluetooth.h"
#include "Accelerometer.h"

void setup() {
  Serial.begin(9600);

  setUpAccelerometer();
  setUpMotors();
  setUpBluetooth();
}

void loop() {
  delay(2);

  accelerometerLoop();
  bluetoothLoop();

  getAndProcessMotorCommand();
}

void getAndProcessMotorCommand() {
  MotorCommand command;
  CONTROL_MODE controlMode = getControlModeFromBluetooth();

  switch(controlMode) {
    case MANUAL:
      command = getCommandFromBluetooth();
      break;
    case SELF_BALANCING:
      command = getCommandFromAccelerometer();
      break;
    default:
      command.action = NONE;
      command.speed = 0;
      break;
  }

  processMotorCommand(command);
}
