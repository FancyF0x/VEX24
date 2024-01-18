#include "api.h"
#include "robot.h"
#include "autons/HelperMethods.h"

inline void runRightAwpAuton() {
    /*
    backWingsDown();
    pros::delay(200);

    driveChassis.MovePid(500, 1, -1, true);
    driveChassis.TurnPid(37, 1.8, 0);
    driveChassis.Move(200, 100, -1, 1000, true);

    frontWingsDown();
    pros::delay(1000);

    frontWingsUp();
    backWingsUp();

    driveChassis.MovePid(-200, 1, -1, true);
    driveChassis.TurnPid(110, 1);
    */
    
    //start holding the triball

    //activate intake and back up
    startIntake();
    pros::delay(300);
    driveChassis.MovePid(-200, 1, -1, true);

    //turn towards goal, move, and turn the rest of the way to the goal
    driveChassis.TurnPid(45, 1);
    driveChassis.MovePid(1000, 1, 5.5, true);
    driveChassis.TurnPid(45, 1);

    //score the triball
    startIntake(false);
    driveChassis.Move(280, 127, 7, 800, true);
    stopIntake();

    //start moving the climber into position
    pros::Task c([]() {
        climbMotor.move_absolute(4800, 100);
    });

    //back up and turn towards the bar
    driveChassis.MovePid(-400,  1, 5, true);
    driveChassis.TurnPid(135, 1);

    //move to be aligned with the bar and turn towards it
    driveChassis.MovePid(1200, 1, 5, true);
    driveChassis.TurnPid(-45, 1);

    //move and touch hang bar
    driveChassis.MovePid(1970, 1, 5, true);
}