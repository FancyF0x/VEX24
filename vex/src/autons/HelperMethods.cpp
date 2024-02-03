#include "robot.h"
#include "api.h"
#include "HelperMethods.h"

void frontWingsOut() {
    frontWings.set_value(1);
}

void frontWingsIn() {
    frontWings.set_value(0);
}

void backWingsOut() {
    backWings.set_value(1);
}

void backWingsIn() {
    backWings.set_value(0);
}

void startIntake(bool in) {
    IntakeMotor.move(in ? -127 : 127);
}

void stopIntake() {
    IntakeMotor.brake();
}