#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "robot.h"

#include "library/CatapultController.h"
#include "library/ChassisController.h"
#include "library/IntakeController.h"

PID drivePid(1, 0, 0);
PID turnPid(1, 0, 0);
Chassis driveChassis(leftMotors, rightMotors, imu, drivePid, turnPid);

//PID cataPid(2, 0, 0);
Catapult cata(cata_motors, cataSensor);

using namespace pros;

void print_debug() {
	lcd::initialize();

	while(true) {
		lcd::set_text(0, "Cata rotation: " + std::to_string(cataSensor.get_position()));
		lcd::set_text(1, "Cata calibrating: " + std::to_string(cata.calibrating));

		delay(20);

		lcd::clear();
	}
}

void initialize() {
	IntakeMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

	cata_motors.set_brake_modes(E_MOTOR_BRAKE_HOLD);
	cata_motors.set_gearing(E_MOTOR_GEAR_100);
	
	cataSensor.set_position(0);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	Task t(print_debug);
	Task c{[=]{
		cata.calibrate(); //watch dem fingers
		cata.load();
	}};

	while(true) {
		//driving
		double leftMove = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		double rightMove = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		driveChassis.DriveTank(leftMove, rightMove);

		//intake
		if(master.get_digital(E_CONTROLLER_DIGITAL_R1))
			IntakeMotor.move(127);
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2))
			IntakeMotor.move(-127);
		else
			IntakeMotor.brake();

		//cata
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
			Task f {[=] {
				cata.fire();
			}};
		}

		//temporary manual override
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
			cata_motors.move(127);

		delay(10);
	}
}
