#include "Actions.h"
#include "Pins.h"
#include "Motors.h"
#include "Bluetooth.h"

void setup() {
  Serial.begin(9600);

  setUpBluetooth();
  setUpMotors();
}

void loop() {
  delay(5);

  MOTOR_ACTIONS action = getActionFromBluetooth();
  processMotorAction(action);
}
