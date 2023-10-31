#include "library/CatapultController.h"
#include "robot.h"
#include <vector>

Catapult::Catapult(pros::MotorGroup &motors, rotation_units &unit,
                   pros::IMU &rotation_sensor) {

  Catapult::motorGroup = &motors;
  Catapult::unit = &unit;
  Catapult::rotation_sensor = &rotation_sensor;
}

void Catapult::turnCatapult(double degrees, float power) {}

void Catapult::turnCatapult(float power) {
  motorGroup->move_velocity((master.get_digital(pros::E_CONTROLLER_DIGITAL_A) -
                             master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) *
                            power);
}

void Catapult::resetMotors() {}

int Catapult::distanceToEncoders() { return 0; }