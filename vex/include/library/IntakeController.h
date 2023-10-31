#pragma once

#include "api.h"
#include "pid.h"

class Intake {

public:
  enum rotation_units { deg, rad };
  Intake(pros::Motor motor1, rotation_units& unit);

  void turnIntake(double degrees, float power);
  void turnIntake(float power);

private:
  pros::Motor *motor;
  rotation_units *unit;

  void resetMotors();
  int distanceToEncoders();
};