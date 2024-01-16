// define robot ports here
#pragma once

#include "api.h"
#include "library/ChassisController.h"
#include "pros/adi.hpp"
#include "pros/misc.h"

#define RIGHT_MOTOR_1_PORT 11
#define RIGHT_MOTOR_2_PORT 13
#define RIGHT_MOTOR_3_PORT 15
#define RIGHT_MOTOR_4_PORT 12

#define LEFT_MOTOR_1_PORT 19
#define LEFT_MOTOR_2_PORT 17
#define LEFT_MOTOR_3_PORT 18
#define LEFT_MOTOR_4_PORT 14

#define OUTTAKE_PORT 20

#define WINGS_PORT 'H'

extern pros::Controller master;

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

extern pros::Motor intakeFold1;
extern pros::Motor intakeFold2;
extern pros::Motor_Group intakeFold;

extern pros::Motor cata1;
extern pros::Motor cata2;
extern pros::Motor_Group cata_motors;
extern pros::Rotation cataSensor;

extern pros::Motor IntakeMotor;

extern pros::Imu imu;

extern pros::ADIDigitalOut wings;