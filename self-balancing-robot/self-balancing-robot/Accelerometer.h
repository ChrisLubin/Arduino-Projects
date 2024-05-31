#include "Wire.h"
#include <MPU6050_light.h>

#define DATA_CHECK_INTERVAL_MILLIS 10

MPU6050 mpu(Wire);

bool isLogging = true;
double currentAngle = 0;

void setUpAccelerometer() {
  digitalWrite(LED_BUILTIN, HIGH);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status != 0) { } // wait for MPU6050 to be ready
  
  digitalWrite(LED_BUILTIN, LOW);
}

void accelerometerLoop() {
  mpu.update();

  currentAngle = mpu.getAngleX();

  if (isLogging) {
    Serial.print("Angle - ");
    Serial.println(currentAngle);
  }
}

MotorCommand getCommandFromAccelerometer() {
  MotorCommand command;
  command.speed = 50;

  if (abs(currentAngle) <= 2) {
    command.action = NONE;
  } else if (currentAngle > 0) {
    command.action = GO_FORWARD;
  } else if (currentAngle < 0) {
    command.action = GO_BACKWARD;
  }

  return command;
}