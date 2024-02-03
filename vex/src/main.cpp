#define KYLE_DRIVING false

#include "main.h"
#include "pros/misc.h"
#include "robot.h"

#include "library/IntakeController.h"

#include <iostream> // for debugging
#include <vector>

//autons:
#include "autons/AWPRight.cpp"

using namespace pros;

bool initializing = false;
double MAX_ACCEL = 130; //edit how fast the bot is allowed to accelerate to avoid tipping

void print_debug() {
	lcd::initialize();

	while(true) {
		delay(10);

		lcd::clear();
	}
}

void initialize() {	
	IntakeMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

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
	static_imu.reset();
	delay(3000);
	imu.tare_rotation();
	static_imu.tare();

	master.clear();
	delay(60);
	master.set_text(0, 0, "Armed");
}

void autonomous() {
	runRightAwpAuton(); //TODO: MAKE AN AUTON SELECTOR
}

double expo(double value, double expo) {
	bool negative = value < 0;

	value /= 127;
	value = pow(value, expo);
	value *= value>0 && negative ? -1 : 1;
	value *= 127;

	return value;
}

double get_avr_speed() {
	std::vector<double> right = rightMotors.get_actual_velocities();
	std::vector<double> left = leftMotors.get_actual_velocities();

	double r_avr = 0;
	for(int i=0; i<right.size(); i++) {
		r_avr += right.at(i);
	}
	r_avr /= right.size();

	double l_avr = 0;
	for(int i=0; i<left.size(); i++) {
		l_avr += left.at(i);
	}
	l_avr /= left.size();

	return (r_avr+l_avr) / 2;
}

void opcontrol() {
	bool frontWingsDeployed = false;
	bool backWingsDeployed = false;
	rightMotors.set_brake_modes(E_MOTOR_BRAKE_COAST);
	leftMotors.set_brake_modes(E_MOTOR_BRAKE_COAST);

	while(true) {
		//driving
		if(KYLE_DRIVING) {
			double leftAmount = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
			double rightAmount = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
			driveChassis.DriveTank(leftAmount, rightAmount);
		}
		else {
			double driveAmount = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
			double turnAmount = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

			//speed control (prevent tipping)
			/*
			if(std::abs(get_avr_speed() - driveAmount) > MAX_ACCEL) {
				driveAmount /= 2;
			}
			*/

			driveChassis.DriveArcade(driveAmount, expo(turnAmount, 3)/2); 
		}

		//intake
		if(master.get_digital(E_CONTROLLER_DIGITAL_R2))
			IntakeMotor.move(127);
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R1))
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

		delay(10);
	}
}
