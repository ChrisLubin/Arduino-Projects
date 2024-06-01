#include "Wire.h"
#include <MPU6050_light.h>
#include <PID_v1.h>

#define DATA_CHECK_INTERVAL_MILLIS 10

MPU6050 mpu(Wire);

bool isLogging = true;


// PID
double targetAngle = -5;
double currentAngle = 0;
double pidOutput;
double kp = 6;
double ki = 1300;
double kd = 0.07;
PID pidController(&currentAngle, &pidOutput, &targetAngle, kp, ki, kd, REVERSE);

void setUpAccelerometer() {
  digitalWrite(LED_BUILTIN, HIGH);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status != 0) { } // wait for MPU6050 to be ready
  
  digitalWrite(LED_BUILTIN, LOW);
  pidController.SetSampleTime(5);
  pidController.SetOutputLimits(-HIGHEST_MOTOR_SPEED, HIGHEST_MOTOR_SPEED);
  pidController.SetMode(AUTOMATIC);
}

void accelerometerLoop() {
  mpu.update();

  currentAngle = mpu.getAngleX();
  pidController.Compute();

  if (isLogging) {
    Serial.print("Current Angle - ");
    Serial.print(currentAngle);
    Serial.print("\t Output - ");
    Serial.println(pidOutput);
  }
}

MotorCommand getCommandFromAccelerometer() {
  MotorCommand command;
  double motorSpeedToUse = abs(pidOutput);
  command.speed = constrain(motorSpeedToUse, LOWEST_MOTOR_SPEED, HIGHEST_MOTOR_SPEED);

  if (pidOutput > 0) {
    command.action = GO_FORWARD;
  } else {
    command.action = GO_BACKWARD;
  }

  return command;
}