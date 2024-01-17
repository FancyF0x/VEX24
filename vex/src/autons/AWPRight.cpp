#include "api.h"
#include "robot.h"
#include "autons/HelperMethods.h"

inline void runRightAwpAuton() {
    backWingsDown();
    pros::delay(200);

    driveChassis.MovePid(500, 1, -1, true);
    driveChassis.TurnPid(30, 1.8, 0);
    driveChassis.Move(800, 90, -1, 1000, true);
}