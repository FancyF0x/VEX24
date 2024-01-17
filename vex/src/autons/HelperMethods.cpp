#include "robot.h"
#include "api.h"
#include "HelperMethods.h"

void frontWingsDown() {
    frontWings.set_value(1);
}

void frontWingsUp() {
    frontWings.set_value(0);
}

void backWingsDown() {
    backWings.set_value(1);
}

void backWingsUp() {
    backWings.set_value(0);
}