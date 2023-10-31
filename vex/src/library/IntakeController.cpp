#include "library/IntakeController.h"
#include "robot.h"
#include <vector>

Intake::Intake(pros::Motor &motor1, rotation_units &unit) {
  Intake::motor = &motor1;
  Intake::unit = &unit;
}

void Intake::turnIntake(float power) {}