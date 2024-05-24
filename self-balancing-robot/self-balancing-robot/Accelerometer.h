#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;

#define DATA_CHECK_INTERVAL_MILLIS 10
bool isLogging = false;
float angleX;
float angleY;
float angleZ;

void setUpAccelerometer() {
  digitalWrite(LED_BUILTIN, HIGH);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status != 0) { } // wait for MPU6050 to be ready
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done calibrating!\n");
  digitalWrite(LED_BUILTIN, LOW);
}

void accelerometerLoop() {
  mpu.update();

  if((millis() - timer) > DATA_CHECK_INTERVAL_MILLIS) {
    angleX = mpu.getAngleX();
    angleY = mpu.getAngleY();
    angleZ = mpu.getAngleZ();
    timer = millis();  
  }

  if (isLogging) {
    Serial.print("X : ");
    Serial.print(mpu.getAngleX());
    Serial.print("\tY : ");
    Serial.print(mpu.getAngleY());
    Serial.print("\tZ : ");
    Serial.println(mpu.getAngleZ());
  }
}

MOTOR_ACTIONS getActionFromAccelerometer() {
  if (abs(angleX) <= 5) {
    return NONE;
  } else if (angleX > 0) {
    return GO_FORWARD;
  } else if (angleX < 0) {
    return GO_BACKWARD;
  } else {
    return NONE;
  }
}