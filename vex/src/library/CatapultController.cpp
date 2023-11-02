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

  int lastPos = catasensor->get_position();

  do { //basically just move until the position of the cata 
    motors->move(127); //move very slowly
    lastPos = catasensor->get_position();

    pros::delay(20);
  } while(lastPos < catasensor->get_position());

  motors->brake();

  pros::delay(300); //give the hardware some time to settle

  catasensor->reset_position();
  resetPoint = 5860; //distance from very top to very bottom

  calibrating = false;
}

void Catapult::load() {
  while(resetPoint - catasensor->get_position() > 10) {
    double speed = 0;

    if(usingPID) {
      speed = pid.calculate(catasensor->get_position()-resetPoint) * 1.2; //*1.2 for an extra umph at the end of the load... shouldn't be an issue
      motors->move(speed); //using move instead of move_velocity to prevent another pid from getting in the way of mine. 
    }
    else {
      speed = 50; //tune this: I don't feel like making this accessable to the client code... shouldn't be an issue but if one does come up it's pretty easy to write... im just lazy...
      motors->move(speed); //let the pros built in pid do its thing
    }
  }

  motors->brake(); //hold up and wait for the launch
  is_loaded = true; //ready to go: let other scripts know
}

//ALL OF THIS SHOULD BE PUT IN A THREAD TO AVOID BLOCKING (unless you want that for auton, idk)
void Catapult::fire(bool instantReload) {
  if(firing)
    return;

  firing=true;
  int lastPos = catasensor->get_position();

  do {
    motors->move(70); //don't have to move fast here
    lastPos = catasensor->get_position();
    pros::delay(20);

  } while(lastPos < catasensor->get_position()); //wait for a large enough shift (cata fired)

  is_loaded = false;

  if(instantReload)
    load(); //run this in a thread because I don't feel like waiting for this to happen

  firing=false;
}