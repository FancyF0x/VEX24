#define ONE_STICK false

#include "main.h"
#include "pros/misc.h"
#include "robot.h"

#include "library/CatapultController.h"
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

void print_debug() {

}

void initialize() {	
	Task t(print_debug);

	// intakeMotors.set_brake_modes(E_MOTOR_BRAKE_HOLD);

	flywheelMotors.set_gearing(E_MOTOR_GEAR_100);

	//cata_motors.set_brake_modes(E_MOTOR_BRAKE_HOLD);
	intakeFold.set_gearing(E_MOTOR_GEAR_100);

	intakeFold.set_brake_modes(E_MOTOR_BRAKE_BRAKE);
	
}

void disabled() {}

void competition_initialize() {
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
	// //unfold then start auton
	// intakeFold.tare_position();

	// if(folded) {
	// 	//unfold
	// 	while((intakeFold.get_positions()[0] + intakeFold.get_positions()[1]) / 2 < 420) {
	// 		intakeFold.move(127);
	// 		delay(10);
	// 	}

	// 	folded = false;
	// 	intakeFold.brake();
	// }

	// //run auton based off of what the user selected
	// switch(selector.getSelected()) {
	// 	case 0:
	// 		runRightAwpAuton();
	// 		break;
	// }
}

void opcontrol() {
	bool isFlyWheelSpinning = false;

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

		

		if(master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			intakeMotors.move(90);
		}
		// else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
		// 	intakeMotors.move(-90);
		// }
		else {
			intakeMotors.brake();
		}

		//intake foldding
		if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
			intakeFold.move(90);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){
			intakeFold.move(-90);
		}
		else {
			intakeFold.brake();
		}

		//flywheel
		if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
			// isFlyWheelSpinning = !isFlyWheelSpinning;
			flywheelMotors.move(127);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
			flywheelMotors.move(-90);
		}
		else{
			flywheelMotors.brake();
		}
		// if(isFlyWheelSpinning){
		// 	flywheelMotors.move(127);
		// }

		delay(10);
	}
}
