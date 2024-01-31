#include "api.h"
#include "robot.h"
#include "autons/HelperMethods.h"

inline void runRightAwpAuton() {
    rightMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
	leftMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);

    //pick up triball under bar and 

    driveChassis.Move(4000, 90, 4, -1);

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