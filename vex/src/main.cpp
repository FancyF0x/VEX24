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

// void print_debug() {}

void initialize() {	
	IntakeMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	climbMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
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
}

void autonomous() {
	runRightAwpAuton(); //TODO: MAKE AN AUTON SELECTOR
}

void opcontrol() {
	bool frontWingsDeployed = false;
	bool backWingsDeployed = false;

	while(true) {
		//driving
		double leftAmount = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		double rightAmount = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		driveChassis.DriveTank(leftAmount, rightAmount);

		//intake
		if(master.get_digital(E_CONTROLLER_DIGITAL_R1))
			IntakeMotor.move(127);
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2))
			IntakeMotor.move(-127);
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

		//climber
		if(master.get_digital(E_CONTROLLER_DIGITAL_UP))
			climbMotor.move(-127);
		else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN))
			climbMotor.move(127);
		else
			climbMotor.brake();


		delay(10);
	}
}
