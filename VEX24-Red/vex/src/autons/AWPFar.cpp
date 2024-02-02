#include "api.h"
#include "robot.h"
#include "autons/HelperMethods.h"

inline void runFarAwpAuton() {
    rightMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
	leftMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);


    pros::delay(200);


    //pick up triball under bar and 

    // driveChassis.Move(500, 90, 4, -1);
    driveChassis.Move(2400, 80, -1, -1, true);
    driveChassis.Turn(-55, 50);
    driveChassis.Move(1350, 60, -1, -1, true);
    driveChassis.Turn(-15, 40);
    startIntake(false);
    driveChassis.Move(500, 60, -1, -1, true);
    driveChassis.Move(-500, 60, -1, -1, true);
    stopIntake();
    driveChassis.Turn(-140, 40);

    driveChassis.Move(500, 60, -1, -1, true);
    backWingsDown();
    pros::delay(500);
    driveChassis.Move(-350, 60, -1,-1, true);
    pros::delay(300);
    driveChassis.Turn(-30, 40);
    pros::delay(200);
    backWingsUp();
    pros::delay(400);
    driveChassis.Turn(-2, 40);
    
    pros::delay(300);
    driveChassis.Move(-700, 60, -1,-1, true);
    pros::delay(300);
    driveChassis.Move(500, 60, -1, -1, true);

    // driveChassis.MovePid(1500, .4, 3, true);
    /*
    startIntake();
    driveChassis.MovePid(700, 0.6, 4, true);
    driveChassis.MovePid(-1600, 0.6, 4, true);
    driveChassis.TurnPid(-90, 0.6);

    //spit it out
    startIntake(false);
    driveChassis.MovePid(200, 1, 7, true);
    stopIntake();
    driveChassis.MovePid(-200, 1, 5, true);

    //turn back towards the match load triball and move
    driveChassis.TurnPid(90, 1);
    driveChassis.MovePid(3000, 1, 5, true);
    */
}