#include "api.h"
#include "robot.h"
#include "autons/HelperMethods.h"

inline void run_skills() {
    backWingsOut();
    static_imu.set_rotation(-135);

    //shimmy shimmy (start facing backwards)
    for(int i=0; i<3; i++) {
        driveChassis.TurnPid(-45, 2, 1);
        driveChassis.TurnPid(45, 2, 1);

        pros::delay(200);
    }

    //turn and deploy front wings
    backWingsIn();
    pros::delay(100);
    driveChassis.TurnPid(5-static_imu.get_rotation(), 2);
    frontWingsOut();
    pros::delay(100);

    //FLOOR IT
    driveChassis.MovePid(5000, 1, 5, true);
}