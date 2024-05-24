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

  MOTOR_ACTIONS action = getActionFromBluetooth();
  processMotorAction(action);
  logAccelerometerData();
}
