//initialize robot components here
#include "pros/misc.h"
#include "robot.h"

pros::Controller master = pros::Controller(pros::E_CONTROLLER_MASTER);

pros::Motor rightMotor1 = pros::Motor(RIGHT_MOTOR_1_PORT, true);
pros::Motor rightMotor2 = pros::Motor(RIGHT_MOTOR_2_PORT, true);
pros::Motor rightMotor3 = pros::Motor(RIGHT_MOTOR_3_PORT, true);
pros::Motor rightMotor4 = pros::Motor(RIGHT_MOTOR_4_PORT, true);

pros::Motor leftMotor1 = pros::Motor(LEFT_MOTOR_1_PORT);
pros::Motor leftMotor2 = pros::Motor(LEFT_MOTOR_2_PORT);
pros::Motor leftMotor3 = pros::Motor(LEFT_MOTOR_3_PORT);
pros::Motor leftMotor4 = pros::Motor(LEFT_MOTOR_4_PORT);

pros::Motor_Group leftMotors = pros::Motor_Group({leftMotor1, leftMotor2, leftMotor3, leftMotor4});
pros::Motor_Group rightMotors = pros::Motor_Group({rightMotor1, rightMotor2, rightMotor3, rightMotor4});

pros::Motor cata1 = pros::Motor(CATA_ONE_PORT);
pros::Motor cata2 = pros::Motor(CATA_TWO_PORT, true);
pros::Motor_Group cata = pros::Motor_Group({cata1,cata2});

pros::Rotation cataSensor = pros::Rotation(CATA_ROT_SENSE_PORT);

pros::Motor IntakeMotor = pros::Motor(INTAKE_PORT);

pros::Imu imu = pros::Imu(INERTIAL_PORT);