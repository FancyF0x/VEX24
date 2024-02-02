#pragma once

#include "api.h"
#include "pid.h"
#include <vector>

class Chassis {
    public:
        //the chassis can be initialized with one of three units of measurement:
        //inches, centimeters, and encoder (raw encoder values of the motors).
        //This is used when driving the chassis a certain distance
        enum drive_units {in, cm, en};

        //use motor encoders to drive
        Chassis(pros::Motor_Group& left, pros::Motor_Group& right, pros::Imu& gyro);
        Chassis(pros::Motor_Group& left, pros::Motor_Group& right, pros::Imu& gyro, drive_units units, double wheelRadius);
        Chassis(pros::Motor_Group& left, pros::Motor_Group& right, pros::Imu& gyro, PID& pid, PID& turnPid);
        Chassis(pros::Motor_Group& left, pros::Motor_Group& right, pros::Imu& gyro, PID& pid, PID& turnPid, drive_units units, double wheelRadius);

        //TODO: use odometers to drive

        void DriveArcade(double drive, double turn, float turn_expo=1, float drive_expo=1);
        void DriveTank(double left, double right);

        void MovePid(double distance, float speed_m, float slewrate=-1, bool inertialLock=false); //with pid
        void Move(double distance, int speed, float slewrate=-1, int timeout=-1, bool inertialLock=false);        //without pid

        void TurnPid(int degrees, float speed_m, int disable=-1);       //with pid (0 to disable left side, 1 to disable right side) (disabling will cause only one side of the wheels to spin)
        void Turn(int degrees, int speed, int disable=-1);                               //without pid

        double getAverageRightPosition(bool rawEncoder);
        double getAverageLeftPosition(bool rawEncoder);
        double getAveragePosition(bool rawEncoder);
    private:
        PID pid;
        PID turnPid;
        drive_units unit;

        pros::Motor_Group* left;
        pros::Motor_Group* right;
        pros::Imu* gyro;

        float wheelRadius;

        void resetMotors();
        int distanceToEncoder(double distance);
        double average(std::vector<double> values);
};