#include "library/CatapultController.h"
#include "pros/rtos.h"

Catapult::Catapult(pros::Motor_Group& catapult_motors, pros::Rotation& catasensor, float resetPoint) {
  Catapult::motors = &catapult_motors;
  Catapult::catasensor = &catasensor;
  usingPID = false;
  Catapult::resetPoint = resetPoint;

  is_loaded = false;
}

Catapult::Catapult(pros::Motor_Group& catapult_motors, pros::Rotation& catasensor, PID& pid, float resetPoint) {
  Catapult::motors = &catapult_motors;
  Catapult::catasensor = &catasensor;
  Catapult::pid = pid;

  usingPID = true;
  Catapult::resetPoint = resetPoint;

  is_loaded = false;
}

void Catapult::calibrate() {
  calibrating = true;
  stop = false;
  int lastPos = catasensor->get_position();

  do { //basically just move until the position of the cata 
    motors->move(127); //move
    lastPos = catasensor->get_position();

    pros::delay(50);
  } while(catasensor->get_position()-lastPos >= 0 && !stop);

  motors->brake();

  pros::delay(800); //give the hardware some time to settle (maybe not needed but idk why not all of this runs before the match starts)

  catasensor->reset_position();
  resetPoint = 5500; //distance from very top to very bottom

  motors->tare_position();

  calibrating = false;
}

void Catapult::load() {
  if(loading || firing)
    return;

  loading = true;
  stop = false;
  while(resetPoint > catasensor->get_position() && !stop) {
    double speed = 0;

    if(usingPID) {
      speed = pid.calculate(catasensor->get_position()-resetPoint) * 1.2; //*1.2 for an extra umph at the end of the load... shouldn't be an issue
      motors->move(speed); //using move instead of move_velocity to prevent another pid from getting in the way of mine. 
    }
    else {
      speed = 50; //tune this: I don't feel like making this accessable to the client code... shouldn't be an issue but if one does come up it's pretty easy to write... im just lazy...
      motors->move_velocity(speed);
    }

    pros::delay(5);
  }

  motors->brake(); //hold up and wait for the launch

  is_loaded = true; //ready to go: let other scripts know
  loading = false;
}

//ALL OF THIS SHOULD BE PUT IN A THREAD TO AVOID BLOCKING (unless you want that for auton, idk)
void Catapult::fire(bool instantReload) {
  if(firing)
    return;

  if(loading) {
    stop = true;
    pros::delay(60);
  }

  if(!is_loaded)
    load();

  firing=true;
  stop = false;

  while(catasensor->get_position() > resetPoint/2 && !stop) {
    motors->move_velocity(100);
    pros::delay(20);
  }

  motors->brake();

  is_loaded = false;
  firing=false;

  if(instantReload)
    load(); //run this in a thread because I don't feel like waiting for this to happen
}