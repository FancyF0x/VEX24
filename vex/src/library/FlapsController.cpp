#include "library/FlapsController.h"
#include "robot.h"

Flaps::Flaps() {
  
}

void Flaps::openFlaps() {
  digitalWrite(OUTTAKE_PORT, HIGH);
}

void Flaps::closeFlaps() {
  digitalWrite(OUTTAKE_PORT, LOW);
}