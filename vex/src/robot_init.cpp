//initialize robot components here
#include "robot.h"

pros::Motor f_rightMotor = pros::Motor(FRONT_RIGHT_MOTOR_PORT, true);
pros::Motor f_leftMotor = pros::Motor(FRONT_LEFT_MOTOR_PORT);
pros::Motor b_rightMotor = pros::Motor(BACK_RIGHT_MOTOR_PORT, true);
pros::Motor b_leftMotor = pros::Motor(BACK_LEFT_MOTOR_PORT);

pros::Motor_Group leftMotors = pros::Motor_Group({f_leftMotor, b_leftMotor});
pros::Motor_Group rightMotors = pros::Motor_Group({f_rightMotor, b_rightMotor});

pros::Imu gyro = pros::Imu(INERTIAL_PORT);