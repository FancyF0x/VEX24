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
Chassis driveChassis(leftMotors, rightMotors, imu, drivePid, turnPid);

//PID cataPid(2, 0, 0);
// Catapult cata(cata_motors, cataSensor);

AutonSelector selector(1);

using namespace pros;

//to keep track of whether or not the bot is folded and how far the motors have to move to folds
bool folded = false;
bool initializing = false;
const int FOLDED_DISTANCE = -450;

void print_debug() {

}

void initialize() {	
	Task t(print_debug);

	// intakeMotors.set_brake_modes(E_MOTOR_BRAKE_HOLD);

	flywheelMotors.set_gearing(E_MOTOR_GEAR_100);

	//cata_motors.set_brake_modes(E_MOTOR_BRAKE_HOLD);
	intakeFold.set_gearing(E_MOTOR_GEAR_100);
	
	//calibrate cata
	//cata.calibrate();
	//cata.load();
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
	// cata.calibrate();
	// Task r {[=] {
	// 	cata.load();
	// }};

	while(true) {
		//driving
		double leftMove = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		double rightMove = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		driveChassis.DriveTank(leftMove, rightMove);

		//intake
		if(master.get_digital(E_CONTROLLER_DIGITAL_R1))
			intakeMotors.move(100);
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2))
			intakeMotors.move(-100);
		else
			intakeMotors.brake();

		//intake foldding
		if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
			intakeFold.move(127);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){
			intakeFold.move(-127);

		}
		else{
			intakeFold.brake();
		}

		//flywheel
		if(master.get_digital(E_CONTROLLER_DIGITAL_X)){
			flywheelMotors.move(127);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_B)){
			flywheelMotors.move(-127);

		}
		else{
			flywheelMotors.brake();
		}


		

		// //cata
		// if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)) {
		// 	std::cout << "X button pressed" << std::endl;
		// 	Task f {[=] {
		// 		cata.fire();
		// 	}};
		// }

		// if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) {
		// 	Task f {[=] {
		// 		cata.load();
		// 	}};
		// }

		// //temporary manual override
		// if(master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
		// 	cata.stop = true; //stops any while loop that's currently running in the cata
		// 	cata_motors.move(127);
		// }
		// else if(!cata.firing)
		// 	cata_motors.brake();

		delay(10);
	}
}
