#include "api.h"
#include "robot.h"
#include "autons/HelperMethods.h"

inline void runRightAwpAuton() {
    rightMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
	leftMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);

    backWingsDown();
    pros::delay(200);

    //push the triball with the wings
    driveChassis.MovePid(500, 1, -1, true);
    driveChassis.TurnPid(37, 1.8, 0);
    driveChassis.Move(200, 60, -1, -1, true);
    driveChassis.Move(-200, 60, -1, -1, true);

    frontWingsDown();
    pros::delay(100);

    //score the tribal
    driveChassis.Move(500, 100, -1, 1300, true);

    frontWingsUp();
    backWingsUp();

    //start raising climber
    // pros::Task c([]() {
    //     climbMotor.move_absolute(4800, 100);
    // });

    driveChassis.MovePid(-200, 1, -1, true);
    driveChassis.TurnPid(135, 1);

    //move and then turn towards hang bar
    driveChassis.MovePid(1130, 1, 5, true);
    driveChassis.TurnPid(-45, 1);

    driveChassis.MovePid(2100, 1, 5, true);
}