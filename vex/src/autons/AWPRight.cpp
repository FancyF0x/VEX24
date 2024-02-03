#include "api.h"
#include "robot.h"

inline void runRightAwpAuton() {

    rightMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
	leftMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);

    while (true) {
        flywheelMotors.move(90);
        intakeMotors.move(50);
        intakeFold.move(90);
    }

    //push the triball with the wings
    driveChassis.MovePid(500, 1, -1, true);
    driveChassis.TurnPid(50, 1.3, 0);
}