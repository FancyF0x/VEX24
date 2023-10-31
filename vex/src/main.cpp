#include "main.h"
#include "pros/misc.h"
#include "robot.h"

#include "library/CatapultController.h"
#include "library/ChassisController.h"
#include "library/IntakeController.h"

PID drivePid(1, 0, 0);
PID turnPid(1, 0, 0);
Chassis driveChassis(leftMotors, rightMotors, imu, drivePid, turnPid);

void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	driveChassis.DriveArcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), pros::E_CONTROLLER_ANALOG_RIGHT_X);
}
