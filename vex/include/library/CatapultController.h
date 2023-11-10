#pragma once

#include "api.h"
#include "pid.h"

class Catapult {
  public:
    Catapult(pros::Motor_Group& catapult_motors, pros::Rotation& catasensor, float resetPoint=0);
    Catapult(pros::Motor_Group& catapult_motors, pros::Rotation& catasensor, PID& pid, float resetPoint=0);

    void calibrate(); //run during initialization: finds what the reset position is. DOES NOT RESET. Call reset after calibrating
    void load(); //reset catapult
    void fire(bool instantReload=true); //fire and then reset for next shot ()

    bool is_loaded;
    bool calibrating = false; //mainly for debugging, but could have some other uses;

    bool firing = false;
    bool stop = false;
    bool loading = false;

  private:
    pros::Motor_Group* motors;
    pros::Rotation* catasensor;
    PID pid;
    float resetPoint;

    bool usingPID;
};