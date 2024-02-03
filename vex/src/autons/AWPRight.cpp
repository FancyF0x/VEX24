#include "api.h"
#include "robot.h"
#include "autons/HelperMethods.h"

inline void runRightAwpAuton() {
    static_imu.set_rotation(0);

    rightMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
	leftMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);

    //pick up triball under bar while moving forward
    startIntake();
    driveChassis.MovePid(2150, 0.6, 3, true);

    //turn to the side
    driveChassis.TurnPid(-90, 1);

    //spit it out
    startIntake(false);
    driveChassis.MovePid(200, 1, 7, true);
    stopIntake();
    driveChassis.MovePid(-200, 1, 5, true);

    //turn back towards the match load triball and move
    driveChassis.TurnPid(85, 1);
    driveChassis.MovePid(500, 1, 5, true);

    //swing turn into place
    driveChassis.TurnPid(-45, 2, 0);

    //deploy wings
    backWingsOut();

    //scoop ball out
    driveChassis.MovePid(500, 1, 4, true);
    driveChassis.TurnPid(-65, 2, 0);
    driveChassis.MovePid(600, 1, 3, true);

    //move back
    backWingsIn();
    driveChassis.MovePid(-600, 1, 5, true);
    driveChassis.TurnPid(30, 1);

    //push triball in and move back out
    //frontWingsOut();
    driveChassis.Move(800, 127, 6, 3000);
    driveChassis.MovePid(-400, 1, 4, true);
    frontWingsIn();
    pros::delay(100);

    //turn backwards and move towards bar
    driveChassis.TurnPid(-5-static_imu.get_rotation(), 1.1); //realign to field
    driveChassis.Move(-2200, 80, 3, -1);
    
    //deploy wings
    backWingsOut();

    driveChassis.MovePid(-800, 1, -1, true);
    driveChassis.Turn(30, 1, 1);

}