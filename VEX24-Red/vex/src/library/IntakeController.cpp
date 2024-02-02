#include "library/IntakeController.h"

Intake::Intake(pros::Motor motor1, rotation_units& unit) {
  Intake::motor = &motor1;
  Intake::unit = &unit;
}

void Intake::turnIntake(float power) {
  // arbitrary controls
  motor->move_velocity(power);
}

void Intake::turnIntake(double degrees, float power) {}

void Intake::resetMotors() {}

int Intake::distanceToEncoders() { return 0; }