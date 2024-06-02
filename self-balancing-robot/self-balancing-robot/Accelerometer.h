#include "Wire.h"
#include <MPU6050_light.h>
#include <PID_v1.h>

#define DATA_CHECK_INTERVAL_MILLIS 10
#define STOP_MOTORS_ANGLE_THRESHOLD 45

MPU6050 mpu(Wire);

bool isLogging = true;


// PID
double targetAngle = -5;
const double ORIGNAL_TARGET_ANGLE = targetAngle;
double currentAngle = 0;
double pidOutput;
double kp = 6;
double ki = 1300;
double kd = 0.07;
double stopMotorsLowAngleThreshold = targetAngle - STOP_MOTORS_ANGLE_THRESHOLD;
double stopMotorsHighAngleThreshold = targetAngle + STOP_MOTORS_ANGLE_THRESHOLD;
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

int getMotorSpeedFromAccelerometer() {
  if (currentAngle < stopMotorsLowAngleThreshold || currentAngle > stopMotorsHighAngleThreshold) {
    return 0;
  }

  return constrain(abs(pidOutput), LOWEST_MOTOR_SPEED, HIGHEST_MOTOR_SPEED);
}

MOTOR_ACTIONS getMotorActionFromAccelerometer() {
  return pidOutput > 0 ? GO_FORWARD : GO_BACKWARD;
}

MotorCommand getCommandFromAccelerometer() {
  MotorCommand command;
  command.speed = getMotorSpeedFromAccelerometer();
  command.action = getMotorActionFromAccelerometer();

  return command;
}

void updateTargetAngleOffsetThreshold() {
  stopMotorsLowAngleThreshold = targetAngle - STOP_MOTORS_ANGLE_THRESHOLD;
  stopMotorsHighAngleThreshold = targetAngle + STOP_MOTORS_ANGLE_THRESHOLD;
}

// Used to move bot forward or backward
void setAccelerometerTargetAngleOffset(double offset) {
  targetAngle = ORIGNAL_TARGET_ANGLE + offset;

  updateTargetAngleOffsetThreshold();
}