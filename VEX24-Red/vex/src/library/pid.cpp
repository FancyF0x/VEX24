#include "library/pid.h"
#include "api.h"

//the robot will use the I term if the error is less than IMax, but greater than IMin
PID::PID(double Kp, double Ki, double Kd, double dt, double IMax, double IMin, double MaxI)
{
  PID::_Kp = Kp;
  PID::_Ki = Ki;
  PID::_Kd = Kd;
  PID::_dt = dt;
  PID::_IMin = IMin;
  PID::_IMax = IMax;
  PID::_MaxI = MaxI;

  PID::_integral = 0;
  PID::_prev_error = 0;
}

double PID::calculate(double error, bool delay)
{
    double p = error * PID::_Kp;

    if(std::abs(PID::_integral) > PID::_MaxI)
        PID::_integral = PID::_MaxI * (PID::_integral<0 ? -1:1);
    if(std::abs(error) > PID::_IMax || std::abs(error) < PID::_IMin)
        PID::_integral = 0;
    else
        PID::_integral += error;

    double i = PID::_integral * PID::_Ki;
    double d = error - PID::_prev_error;
    PID::_prev_error = error;

    if(delay)
      pros::delay(PID::_dt);

    return p + i + d;
}