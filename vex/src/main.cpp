#include "main.h"
#include "pros/misc.h"
#include "robot.h"

#include "library/CatapultController.h"
#include "library/ChassisController.h"
#include "library/IntakeController.h"

PID drivePid(1, 0, 0);
PID turnPid(1, 0, 0);
Chassis driveChassis(leftMotors, rightMotors, imu, drivePid, turnPid);
//Intake intake(IntakeMotor, Intake::rotation_units::deg);

void initialize() {
	IntakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	while(true) {
		double forwardMove = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		double turnMove = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		driveChassis.DriveArcade(forwardMove, turnMove);

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
			IntakeMotor.move(127);
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
			IntakeMotor.move(-127);
		else
			IntakeMotor.brake();

		pros::delay(10);
	}
}
