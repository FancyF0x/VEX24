#include "api.h"
#include "robot.h"

inline void runRightAwpAuton() {
    driveChassis.MovePid(2000, 1, 5);
    driveChassis.MovePid(-2000, 1, 5);
}