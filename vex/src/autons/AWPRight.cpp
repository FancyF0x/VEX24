#include "api.h"
#include "robot.h"

void runRightAwpAuton() {
    driveChassis.MovePid(1000, 0.4, 5);
}