#include "api.h"
#include "robot.h"

#include "library/ChassisController.h"
#include "library/CatapultController.h"

void runRightAwpAuton(Chassis& driveChassis, Catapult& cata) {
    //turn to push preload into goal
    driveChassis.TurnPid(-45, 1);

    //turn to match load thingy
    driveChassis.TurnPid(90, 1);

    //fire cata and move cata to half way point (to keep the blue triball from getting stuck in the cata)
    cata.fire(false);
    cata.load(true);

    //move
    driveChassis.MovePid(10, 1);

    //turn towards goal
    driveChassis.TurnPid(45, 1);

    //pick up blue triball

    //back away from match load

    //turn towards goal and move

    //outtake colored triball into goal
}