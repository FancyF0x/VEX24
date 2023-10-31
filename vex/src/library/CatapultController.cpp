#include "library/CatapultController.h"
#include <vector>

Catapult::Catapult(pros::MotorGroup &motors, rotation_units &unit,
                   pros::IMU &rotation_sensor) {

  Catapult::motorGroup = &motors;
  Catapult::unit = &unit;
  Catapult::rotation_sensor = &rotation_sensor;
}

void Catapult::turnCatapult(double degrees, float power) {}