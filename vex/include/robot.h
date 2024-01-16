// define robot ports here
#pragma once

#include "api.h"
#include "library/ChassisController.h"
#include "pros/adi.hpp"
#include "pros/misc.h"

#define RIGHT_MOTOR_1_PORT 6
#define RIGHT_MOTOR_2_PORT 7
#define RIGHT_MOTOR_3_PORT 8
#define RIGHT_MOTOR_4_PORT 9

#define LEFT_MOTOR_1_PORT 1
#define LEFT_MOTOR_2_PORT 2
#define LEFT_MOTOR_3_PORT 3
#define LEFT_MOTOR_4_PORT 4

//LEFT = 1, RIGHT = 2
#define INTAKE_FOLD_1_PORT 16
#define INTAKE_FOLD_2_PORT 18

#define FLYWHEEL_LOW_1_PORT 11
#define FLYWHEEL_LOW_2_PORT 13
#define FLYWHEEL_HIGH_1_PORT 12
#define FLYWHEEL_HIGH_2_PORT 14

#define INTAKE_1_PORT 17
#define INTAKE_2_PORT 19

#define INERTIAL_PORT 20 //we dont have a imu atm


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

extern pros::Motor flywheelLow1;
extern pros::Motor flywheelLow2;
extern pros::Motor flywheelHigh1;
extern pros::Motor flywheelHigh2;
extern pros::Motor_Group flywheelMotors;

extern pros::Motor intakeMotor1;
extern pros::Motor intakeMotor2;
extern pros::Motor_Group intakeMotors;

extern pros::Imu imu;

// extern pros::ADIDigitalOut wings;