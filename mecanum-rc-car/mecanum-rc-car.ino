#include "Helpers.h"
#include "Actions.h"
#include "Pins.h"
#include "Motors.h"
#include "Bluetooth.h"
#include "AutonomousMode.h"

void setup() {
  Serial.begin(9600);

  setUpMotors();
  setUpAutonomousMode();
  setUpBluetooth();
}

void loop() {
  delay(5);
  CONTROL_MODE controlMode = getControlModeFromBluetooth();

  bluetoothLoop();
  autonomousModeLoop(controlMode);

  getAndProcessMotorAction(controlMode);
}

void getAndProcessMotorAction(CONTROL_MODE controlMode) {
  MOTOR_ACTIONS action;

  switch(controlMode) {
    case MANUAL:
      action = getMotorActionFromBluetooth();
      break;
    case AUTONOMOUS:
      action = getMotorActionFromAutonomousMode();
      break;
    default:
      action = NONE;
      break;
  }

  processMotorAction(action);
}
