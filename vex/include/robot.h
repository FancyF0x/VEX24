//define robot ports here
#pragma once

#include "api.h"
#include "library/ChassisController.h"

#define RIGHT_MOTOR_1_PORT 1
#define RIGHT_MOTOR_2_PORT 3
#define RIGHT_MOTOR_3_PORT 4
#define RIGHT_MOTOR_4_PORT 5

#define LEFT_MOTOR_1_PORT 7
#define LEFT_MOTOR_2_PORT 8
#define LEFT_MOTOR_3_PORT 9
#define LEFT_MOTOR_4_PORT 10

#define CATA_ONE_PORT 11
#define CATA_TWO_PORT 20
#define CATA_ROT_SENSE_PORT 13

#define INTAKE_PORT 12

#define INERTIAL_PORT          6

extern pros::Motor rightMotor1;
extern pros::Motor rightMotor2;
extern pros::Motor rightMotor3;
extern pros::Motor rightMotor4;

extern pros::Motor leftMotor1;
extern pros::Motor leftMotor2;
extern pros::Motor leftMotor3;
extern pros::Motor leftMotor4;

extern pros::Motor_Group leftMotors;
extern pros::Motor_Group rightMotors;

extern pros::Motor cata1;
extern pros::Motor cata2;
extern pros::Motor_Group cata_motors;
extern pros::Rotation cataSensor;

extern pros::Motor IntakeMotor;

extern pros::Imu imu;