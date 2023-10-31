#pragma once

class PID {
  public:
    PID();
    PID(double Kp, double Ki, double Kd, double dt, double IMax, double IMin, double MaxI);
    PID(double Kp, double Ki, double Kd, double dt, double IMax, double IMin);
    PID(double Kp, double Ki, double Kd, double dt);
    PID(double Kp, double Ki, double Kd);

    double calculate(double error, bool delay=true); //returns the output of the desired pid
    void reset(); //resetting if the user wishes to perform the same pid more than once

    double error; //so that the user can keep track of how far along the robot is

  private:
    double _Kp;
    double _Ki;
    double _Kd;
    double _dt;
    double _endpoint;
    double _integral;
    double _prev_error;
    double _IMin;
    double _IMax;
    double _MaxI;
};