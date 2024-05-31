#ifndef Actions_h
#define Actions_h

#define DONT_CHANGE_SPEED_VALUE -1

enum MOTOR_ACTIONS
{
  NONE,
  GO_FORWARD,
  GO_BACKWARD,
  ROTATE_LEFT_IN_PLACE,
  ROTATE_RIGHT_IN_PLACE,
  ROTATE_LEFT_IN_CIRCLE,
  ROTATE_RIGHT_IN_CIRCLE,
  INCREASE_SPEED,
  DECREASE_SPEED
};

struct MotorCommand {
  MOTOR_ACTIONS action;
  int speed;
};

enum CONTROL_MODE
{
  MANUAL,
  SELF_BALANCING
};

#endif
