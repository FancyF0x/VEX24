#define TESTING true

#include "main.h"
#include "robot.h"

#include "library/CatapultController.h"
#include "library/ChassisController.h"
#include "library/IntakeController.h"
#include "library/AutonSelector.h"

#include <iostream> // for debugging

#include "autons/AWPRight.cpp"

PID drivePid(1, 0, 0);
PID turnPid(1, 0, 0);
Chassis driveChassis(leftMotors, rightMotors, imu, drivePid, turnPid, Chassis::drive_units::in, 3.5);

//PID cataPid(2, 0, 0);
Catapult cata(cata_motors, cataSensor);

AutonSelector selector(1);

using namespace pros;

//to keep track of whether or not the bot is folded and how far the motors have to move to folds
bool folded = false;
bool initializing = false;
const int FOLDED_DISTANCE = -450;

void print_debug() {
	lcd::initialize();
	int line = 0;

	while(true) {
		line = 0;
		lcd::set_text(line++, "Cata rotation: " + std::to_string(cataSensor.get_position()));
		lcd::set_text(line++, "Cata calibrating: " + std::to_string(cata.calibrating));
		lcd::set_text(line++, "Cata loaded: " + std::to_string(cata.is_loaded));
		lcd::set_text(line++, "Cata loading: " + std::to_string(cata.loading));
		lcd::set_text(line++, "Intake fold 1 pos: " + std::to_string(intakeFold1.get_position()));
		lcd::set_text(line++, "Cata firing: " + std::to_string(cata.firing));
		lcd::set_text(line++, "Cata temp: " + std::to_string(cata_motors.get_temperatures()[0]));

		delay(20);

		lcd::clear();
	}
}

void initialize() {	
	Task t(print_debug);

	IntakeMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

	cata_motors.set_gearing(E_MOTOR_GEAR_100);
	//cata_motors.set_brake_modes(E_MOTOR_BRAKE_HOLD);
	intakeFold.set_gearing(E_MOTOR_GEAR_100);
	
	cataSensor.set_position(0);

	//calibrate cata
	cata.calibrate();
	Task r {[=] {
		cata.load();
	}};
}

void disabled() {}

void competition_initialize() {
	folded = true;

	//add the autons to the selector
	selector.add("Right Side AWP", "Push in preload", "score blue+hang");

	//Allow the user to select an auton
	while(true) {
		selector.display_autons(); //update screen

		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP))
			selector.iterate();

		delay(15);
  	}
}

void autonomous() {
	//unfold then start auton
	if(!TESTING) {
		intakeFold.tare_position();

		if(folded) {
			//unfold
			while((intakeFold.get_positions()[0] + intakeFold.get_positions()[1]) / 2 < 420) {
				intakeFold.move(127);
				delay(10);
			}

			folded = false;
			intakeFold.brake();
		}
	}

	//run auton based off of what the user selected
	switch(selector.getSelected()) {
		case 0:
			runRightAwpAuton(driveChassis, cata);
			break;
	}
}

void opcontrol() {
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
			std::cout << "X button pressed" << std::endl;
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
		else if(!cata.firing)
			cata_motors.brake();

		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
			wingsDeployed = !wingsDeployed;
			wings.set_value(wingsDeployed);
		}

		delay(10);
	}
}
