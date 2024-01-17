#pragma once

class PID {
  public:
    PID(double Kp=1, double Ki=0, double Kd=0, double dt=20, double IMax=20, double IMin=5, double MaxI=65);

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