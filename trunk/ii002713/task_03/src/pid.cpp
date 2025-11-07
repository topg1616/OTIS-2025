#include "pid.h"

PID::PID(double K_, double T_, double TD_, double T0_)
    : K(K_), T(T_), TD(TD_), T0(T0_),
      e0(0.0), e1(0.0), e2(0.0), u(0.0) 
{
    q0 = K * (1.0 + T0 / T + TD / T0);
    q1 = -K * (1.0 + 2.0 * TD / T0 - T0 / T);
    q2 = K * (TD / T0);
}

double PID::compute(double y, double yzad) {
    e2 = e1;
    e1 = e0;
    e0 = yzad - y;

    double du = q0 * e0 + q1 * e1 + q2 * e2;
    u += du;
    return u;
}

void PID::reset() {
    e0 = e1 = e2 = u = 0.0;
}
