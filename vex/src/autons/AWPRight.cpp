#include "api.h"
#include "robot.h"

inline void runRightAwpAuton() {
    driveChassis.MovePid(1000, 1, 5);
    driveChassis.TurnPid(180, 1);
    driveChassis.MovePid(1000, 1, 5);
    driveChassis.TurnPid(180, 1);
}