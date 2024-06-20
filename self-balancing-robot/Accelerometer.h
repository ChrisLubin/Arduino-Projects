#include "Wire.h"
#include <MPU6050_light.h>
#include <PID_v1.h>

#define START_BALANCING_ANGLE_THRESHOLD 2
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

void updateCurrentAngle() {
  mpu.update();
  currentAngle = mpu.getAngleX();
}

void setUpAccelerometer() {
  digitalWrite(LED_BUILTIN, HIGH);
  Wire.begin();
  
  byte status = mpu.begin();
  while(status != 0) { } // wait for MPU6050 to be ready
  println(isLogging, "MPU6050 is ready");

  println(isLogging, "Calibrating currentAngle val...");
  for (int i = 0; i < 200; i++) {
    delay(1);
    updateCurrentAngle();
  }

  println(isLogging, "Waiting for the robot to be centered...");
  while(abs(currentAngle - targetAngle) > START_BALANCING_ANGLE_THRESHOLD) {
    delay(2);
    updateCurrentAngle();
  }

  digitalWrite(LED_BUILTIN, LOW);
  pidController.SetSampleTime(5);
  pidController.SetOutputLimits(-HIGHEST_MOTOR_SPEED, HIGHEST_MOTOR_SPEED);
  pidController.SetMode(AUTOMATIC);
}

void accelerometerLoop() {
  updateCurrentAngle();
  pidController.Compute();

  print(isLogging, "Current Angle - ");
  print(isLogging, currentAngle);
  print(isLogging, "\t Output - ");
  println(isLogging, pidOutput);
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

void setAccelerometerTuningVal(PID_TUNINGS parameter, double val) {
  if (val == DO_NOT_CHANGE_PID_VAL) {
    return;
  }

  switch(parameter) {
    case P:
      kp = val;
      break;
    case I:
      ki = val;
      break;
    case D:
      kd = val;
      break;
    default:
      return;
  }

  pidController.SetTunings(kp, ki, kd);
}

double getAccelerometerAngleDiff() {
  return currentAngle - targetAngle;
}
