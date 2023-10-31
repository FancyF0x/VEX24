#include "library/IntakeController.h"
#include "pros/misc.h"
#include "robot.h"
#include <vector>

Intake::Intake(pros::Motor &motor1, rotation_units &unit) {
  Intake::motor = &motor1;
  Intake::unit = &unit;
}

void Intake::turnIntake(float power) {
  // arbitrary controls
  motor->move_velocity((master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) -
                        master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) *
                       power);
}

void Intake::turnIntake(double degrees, float power) {}

void Intake::resetMotors() {}

int Intake::distanceToEncoders() { return 0; }