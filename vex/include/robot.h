//define robot ports here
#include "api.h"
#include "library/ChassisController.h"

#define FRONT_RIGHT_MOTOR_PORT 10
#define FRONT_LEFT_MOTOR_PORT  8
#define BACK_RIGHT_MOTOR_PORT  20
#define BACK_LEFT_MOTOR_PORT   17

#define INERTIAL_PORT          6

extern pros::Motor f_rightMotor;
extern pros::Motor f_leftMotor;
extern pros::Motor b_rightMotor;
extern pros::Motor b_leftMotor;

extern pros::Motor_Group leftMotors;
extern pros::Motor_Group rightMotors;

extern pros::Imu gyro;