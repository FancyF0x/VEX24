//initialize robot components here
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "robot.h"

pros::Controller master = pros::Controller(pros::E_CONTROLLER_MASTER);

pros::Motor rightMotor1 = pros::Motor(RIGHT_MOTOR_1_PORT);
pros::Motor rightMotor2 = pros::Motor(RIGHT_MOTOR_2_PORT, true);
pros::Motor rightMotor3 = pros::Motor(RIGHT_MOTOR_3_PORT);
pros::Motor rightMotor4 = pros::Motor(RIGHT_MOTOR_4_PORT, true);

pros::Motor leftMotor1 = pros::Motor(LEFT_MOTOR_1_PORT, true);
pros::Motor leftMotor2 = pros::Motor(LEFT_MOTOR_2_PORT);
pros::Motor leftMotor3 = pros::Motor(LEFT_MOTOR_3_PORT, true);
pros::Motor leftMotor4 = pros::Motor(LEFT_MOTOR_4_PORT);

pros::Motor_Group leftMotors = pros::Motor_Group({leftMotor1, leftMotor2, leftMotor3, leftMotor4});
pros::Motor_Group rightMotors = pros::Motor_Group({rightMotor1, rightMotor2, rightMotor3, rightMotor4});

pros::Motor intakeFold1 = pros::Motor(INTAKE_FOLD_1_PORT);
pros::Motor intakeFold2 = pros::Motor(INTAKE_FOLD_2_PORT, true);
pros::Motor_Group intakeFold = pros::Motor_Group({intakeFold1, intakeFold2});

pros::Motor flywheel1 = pros::Motor(FLYWHEEL_1_PORT, true);
pros::Motor flywheel2 = pros::Motor(FLYWHEEL_2_PORT, true);
pros::Motor flywheel3 = pros::Motor(FLYWHEEL_3_PORT);

pros::Motor_Group flywheelMotors = pros::Motor_Group({flywheel1, flywheel2, flywheel3});

pros::Motor intakeMotor1 = pros::Motor(INTAKE_1_PORT);
pros::Motor intakeMotor2 = pros::Motor(INTAKE_2_PORT, true);
pros::Motor_Group intakeMotors = pros::Motor_Group({intakeMotor1, intakeMotor2});



pros::Imu imu = pros::Imu(INERTIAL_PORT);
