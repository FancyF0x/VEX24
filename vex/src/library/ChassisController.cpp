#include "library/ChassisController.h"
#include <vector>

#define PI 3.1415926

Chassis::Chassis(pros::Motor_Group& left, pros::Motor_Group& right, pros::Imu& gyro) {
    Chassis::left = &left;
    Chassis::right = &right;
    Chassis::gyro = &gyro;

    Chassis::unit = Chassis::drive_units::en;
    Chassis::wheelRadius = 0;

    Chassis::pid = PID(1, 0, 0);
    Chassis::turnPid = PID(4, 0, 0);
}

Chassis::Chassis(pros::Motor_Group& left, pros::Motor_Group& right, pros::Imu& gyro, drive_units units, double wheelRadius) {
    Chassis::left = &left;
    Chassis::right = &right;
    Chassis::gyro = &gyro;
    
    Chassis::unit = units;
    Chassis::wheelRadius = wheelRadius;

    Chassis::pid = PID(1, 0, 0);
    Chassis::turnPid = PID(4, 0, 0);
}

Chassis::Chassis(pros::Motor_Group& left, pros::Motor_Group& right, pros::Imu& gyro, PID& pid, PID& turnPid) {
    Chassis::left = &left;
    Chassis::right = &right;
    Chassis::gyro = &gyro;

    Chassis::unit = Chassis::drive_units::en;
    Chassis::wheelRadius = 0;

    Chassis::pid = pid;
    Chassis::turnPid = turnPid;
}

Chassis::Chassis(pros::Motor_Group& left, pros::Motor_Group& right, pros::Imu& gyro, PID& pid, PID& turnPid, drive_units units, double wheelRadius) {
    Chassis::left = &left;
    Chassis::right = &right;
    Chassis::gyro = &gyro;

    Chassis::unit = units;
    Chassis::wheelRadius = wheelRadius;

    Chassis::pid = pid;
    Chassis::turnPid = turnPid;
}

void Chassis::Move(double distance, float speed_m, float slewrate) {
    resetMotors();

    double slew=0;

    while(std::abs(distanceToEncoder(distance)-getAveragePosition(true)) > 3) {
        double s = pid.calculate(distance-getAveragePosition(true), false) * speed_m;

        if(slewrate>0 && slew<s) {
            s = slew;
            slew += slewrate;
        }

        right->move(s);
        left->move(s);

        pros::delay(20);
    }

    right->brake();
    left->brake();
}

void Chassis::Move(double distance, int speed, float slewrate) {
    resetMotors();

    double slew=0;

    while(std::abs(distanceToEncoder(distance)-getAveragePosition(true)) > 3) {
        int s = speed * (distance<0?-1:1);

        if(slewrate>0 && slew<s) {
            s = (int)slew;
            slew += slewrate * (distance<0?-1:1);
        }

        right->move(s);
        left->move(s);

        pros::delay(20);
    }

    right->brake();
    left->brake();
}

void Chassis::Turn(int degrees, float speed_m) {
    gyro->tare_rotation();

    while(std::abs(degrees - gyro->get_rotation()) > 3) {
        double s = turnPid.calculate(degrees-gyro->get_rotation(), false) * speed_m;

        right->move(-s);
        left->move(s);

        pros::delay(20);
    }

    right->brake();
    left->brake();
}

void Chassis::Turn(int degrees, int speed) {
    gyro->tare_rotation();

    while(std::abs(degrees - gyro->get_rotation()) > 3) {
        double s = speed * (degrees<0?-1:1);

        right->move(-s);
        left->move(s);

        pros::delay(20);
    }

    right->brake();
    left->brake();
}

double Chassis::getAverageRightPosition(bool rawEncoder) {
    std::vector<double> positions = right->get_positions();
    double total = 0;
    for(int i=0; i<positions.size(); i++)
        total += positions[i];
    total /= positions.size();

    //translate the distances into the correct units
    if(!rawEncoder && unit == drive_units::in || unit == drive_units::cm)
        return (total / 360) * (2*PI*wheelRadius);
    
    return total;
}

double Chassis::getAverageLeftPosition(bool rawEncoder) {
    std::vector<double> positions = left->get_positions();
    double total = 0;
    for(int i=0; i<positions.size(); i++)
        total += positions[i];
    total /= positions.size();

    //translate the distances into the correct units
    if(!rawEncoder && unit == drive_units::in || unit == drive_units::cm)
        return (total / 360) * (2*PI*wheelRadius);

    return total;
}

double Chassis::getAveragePosition(bool rawEncoder) {
    return (getAverageRightPosition(rawEncoder) + getAverageLeftPosition(rawEncoder)) / 2;
}

void Chassis::resetMotors() {
    right->tare_position();
    left->tare_position();
}

int Chassis::distanceToEncoder(double distance) {
    if (unit == drive_units::in || unit == drive_units::cm)
        return (int)((distance / (2*PI*wheelRadius)) * 360);
    else
        return (int)distance;
}