#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;

#define DATA_CHECK_INTERVAL_MILLIS 10

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
  Serial.println("Done!\n");
  digitalWrite(LED_BUILTIN, LOW);
}

void logAccelerometerData()
{
  mpu.update();
  
  if((millis() - timer) > DATA_CHECK_INTERVAL_MILLIS) {
    Serial.print("X : ");
    Serial.print(mpu.getAngleX());
    Serial.print("\tY : ");
    Serial.print(mpu.getAngleY());
    Serial.print("\tZ : ");
    Serial.println(mpu.getAngleZ());
    timer = millis();  
  }
}
