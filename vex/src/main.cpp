#define ONE_STICK false

#include "main.h"
#include "pros/misc.h"
#include "robot.h"

#include "library/IntakeController.h"
#include "library/AutonSelector.h"

#include <iostream> // for debugging

//autons:
#include "autons/AWPRight.cpp"

AutonSelector selector(1);

using namespace pros;

bool initializing = false;

void print_debug() {
	lcd::initialize();

	while(true) {
		// lcd::set_text(2, "Static imu: " + std::to_string(static_imu.get_rotation()));

		delay(10);

		lcd::clear();
	}
}

void initialize() {	
	IntakeMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

	Task t(print_debug);
}

void disabled() {}

void competition_initialize() {
	/*
	//add the autons to the selector
	selector.add("Right Side AWP", "Push in preload", "score blue+hang");
	bool updateScreen = false;

	master.clear();

	//Allow the user to select an auton
	while(true) {
		if(updateScreen) {
			selector.display_autons(); //update screen
			updateScreen = false;
		}

		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) {
			selector.iterate();
			updateScreen = true;
		}

		delay(10);
  	}
	*/

	//calibrate imu (blocking)
	master.clear();
	delay(60);
	master.set_text(0, 0, "Calibrating...");
	delay(60);

	imu.reset();
	// static_imu.reset();
	delay(3000);
	imu.tare_rotation();
	// static_imu.tare();

	master.clear();
	delay(60);
	master.set_text(0, 0, "Armed");
}

void autonomous() {
	runRightAwpAuton(); //TODO: MAKE AN AUTON SELECTOR
}

void opcontrol() {
	bool frontWingsDeployed = false;
	bool backWingsDeployed = false;
	rightMotors.set_brake_modes(E_MOTOR_BRAKE_COAST);
	leftMotors.set_brake_modes(E_MOTOR_BRAKE_COAST);

	while(true) {
		//driving
		if(ONE_STICK){
			double leftMove = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
			double rightMove = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
			driveChassis.DriveArcade(leftMove, rightMove);	
		}
		else{
			double leftAmount = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
			double rightAmount = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
			driveChassis.DriveArcade(leftAmount, rightAmount);
		}
		

		//intake
		if(master.get_digital(E_CONTROLLER_DIGITAL_R1))
			IntakeMotor.move(127);
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2))
			IntakeMotor.move(-70);
		else
			IntakeMotor.brake();

		//wings
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) {
			frontWingsDeployed = !frontWingsDeployed;
			frontWings.set_value(frontWingsDeployed);
		}
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)) {
			backWingsDeployed = !backWingsDeployed;
			backWings.set_value(backWingsDeployed);
		}


		delay(10);
	}
}
