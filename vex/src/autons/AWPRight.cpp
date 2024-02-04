#include "api.h"
#include "robot.h"
#include "autons/HelperMethods.h"

inline void runRightAwpAuton() {
    //set the start position of the robot
    // static_imu.set_rotation(-111);

    rightMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
	leftMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);

    // backWingsDown();
    pros::delay(200);

    //push the triball with the wings
    driveChassis.MovePid(-1000, 1, -1, true);

    driveChassis.MovePid(500, 1, -1, true);

    // driveChassis.TurnPid(50, 1.3, 0);

    // driveChassis.Move(300, 127, -1, -1, true);
    // driveChassis.Move(-300, 127, -1, -1, true);

    // //push the triball forward using the front wings
    // frontWingsDown();

    // driveChassis.Move(200, 60, -1, -1, true);
    // // backWingsUp();
    // driveChassis.Move(-350, 40, -1, -1, true);

    // frontWingsUp();
    // driveChassis.TurnPid(-40, 1);

    // driveChassis.Move(350, 100, 6, 2000, false);
    
    // //turn to face the goal and push the triball the rest of the way in
    // driveChassis.TurnPid(30, 1);
    // driveChassis.Move(240, 100, -1, 1000, false);
    // driveChassis.Move(-300, 127, 5, -1, true);

    // //turn away from goal
    // driveChassis.TurnPid(125, 1);

    // //realign to field
    // // driveChassis.TurnPid(45-static_imu.get_rotation(), 1);
    
    // //start raising hang bar
    // pros::Task([]() {
    // });

    // //drive to align with hanging bar
    // driveChassis.MovePid(900, 1, 4, true);

    // // driveChassis.TurnPid(-static_imu.get_rotation(), 1);
    // driveChassis.Move(2500, 80, 6, 5000);
}