#include "library/IntakeController.h"
#include <vector>

Intake::Intake(pros::Motor &motor1, rotation_units &unit) {
  Intake::motor = &motor1;
  Intake::unit = &unit;
}