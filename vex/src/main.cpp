#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
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
		lcd::set_text(2, "Cata loaded: " + std::to_string(cata.is_loaded));
		lcd::set_text(3, "Intake fold 1 pos: " + std::to_string(intakeFold1.get_position()));
		lcd::set_text(4, "Intake fold 2 pos: " + std::to_string(intakeFold2.get_position()));

		delay(20);

		lcd::clear();
	}
}

void initialize() {
	IntakeMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	cata_motors.set_gearing(E_MOTOR_GEAR_100);
	intakeFold.set_gearing(E_MOTOR_GEAR_100);
	
	cataSensor.set_position(0);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	Task t(print_debug);
	cata.calibrate();

	bool wingsDeployed = false;

	/*
	Task c{[=]{
		cata.calibrate(); //watch dem fingers
		//cata.load();
	}};
	*/

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
		if(master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
			cata.stop = true; //stops any while loop that's currently running in the cata
			cata_motors.move(127);
		}
		else
			cata_motors.brake();

		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
			wingsDeployed = !wingsDeployed;
			wings.set_value(wingsDeployed);
		}

		delay(10);
	}
}
