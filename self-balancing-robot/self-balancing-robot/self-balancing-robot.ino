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
  delay(5);

  accelerometerLoop();
  bluetoothLoop();

  getAndProcessMotorAction();
}

void getAndProcessMotorAction() {
  MOTOR_ACTIONS action;
  CONTROL_MODE controlMode = getControlModeFromBluetooth();

  switch(controlMode) {
    case MANUAL:
      action = getActionFromBluetooth();
      break;
    case SELF_BALANCING:
      action = getActionFromAccelerometer();
      break;
    default:
      action = NONE;
      break;
  }

  processMotorAction(action);
}