#pragma once

#include "api.h"
#include "pid.h"

class Catapult {

public:
  enum rotation_units { deg, rad };
  Catapult(pros::MotorGroup &motors, rotation_units &unit,
           pros::IMU &rotation_sensor);

  void turnCatapult(double degrees, float power);

private:
  pros::MotorGroup *motorGroup;

  rotation_units *unit;

  pros::IMU *rotation_sensor;

  void resetMotors();
  int distanceToEncoders();
};