#include "main.h"
#include "robot.h"

#include "library/ChassisController.h"
#include "library/IntakeController.h"
#include "library/AutonSelector.h"

#include <iostream> // for debugging

#include "autons/AWPRight.cpp"

PID drivePid(1, 0, 0);
PID turnPid(1, 0, 0);
Chassis driveChassis(leftMotors, rightMotors, imu, drivePid, turnPid);

AutonSelector selector(1);

using namespace pros;
bool folded = false;
bool initializing = false;
const int FOLDED_DISTANCE = -450;

// void print_debug() {}

void initialize() {	
	IntakeMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

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

		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
			wingsDeployed = !wingsDeployed;
			wings.set_value(wingsDeployed);
		}

		delay(10);
	}
}
