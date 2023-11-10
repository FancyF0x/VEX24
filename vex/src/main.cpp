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

//to keep track of whether or not the bot is folded and how far the motors have to move to folds
bool folded = false;
const int FOLDED_DISTANCE = -450;

void print_debug() {
	lcd::initialize();

	while(true) {
		lcd::set_text(0, "Cata rotation: " + std::to_string(cataSensor.get_position()));
		lcd::set_text(1, "Cata calibrating: " + std::to_string(cata.calibrating));
		lcd::set_text(2, "Cata loaded: " + std::to_string(cata.is_loaded));
		lcd::set_text(3, "Intake fold 1 pos: " + std::to_string(intakeFold1.get_position()));
		lcd::set_text(4, "Intake fold 2 pos: " + std::to_string(intakeFold2.get_position()));
		lcd::set_text(5, "Cata firing: " + std::to_string(cata.firing));
		lcd::set_text(6, "Cata temp: " + std::to_string(cata_motors.get_temperatures()[0]));

		delay(20);

		lcd::clear();
	}
}

void initialize() {
	IntakeMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

	cata_motors.set_gearing(E_MOTOR_GEAR_100);
	//cata_motors.set_brake_modes(E_MOTOR_BRAKE_HOLD);
	intakeFold.set_gearing(E_MOTOR_GEAR_100);
	
	cataSensor.set_position(0);
}

void disabled() {}

void competition_initialize() {
	//oragami (fold up to avoid rule breaking)
	intakeFold.tare_position();

	while((intakeFold.get_positions()[0] + intakeFold.get_positions()[1]) / 2 > FOLDED_DISTANCE) {
		intakeFold.move(-127);
		delay(10);
	}

	folded = true;
	intakeFold.brake();
}

void autonomous() {
	//unfold then start auton
	if(folded) {
		while((intakeFold.get_positions()[0] + intakeFold.get_positions()[1]) / 2 < 20) {
			intakeFold.move(127);
			delay(10);
		}

		folded = false;
		intakeFold.brake();
	}

	//run auton
}

void opcontrol() {
	Task t(print_debug);
	cata.calibrate();
	Task r {[=] {
		cata.load();
	}};

	bool wingsDeployed = false;

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
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)) {
			Task f {[=] {
				cata.fire();
			}};
		}

		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) {
			Task f {[=] {
				cata.load();
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
