#include "pid.h"

PID::PID(double k, double t) {
    K = k;
    T = t;
}

double PID::compute(double e) {
    // Пример дискретного ПИД
    const double kp = K;
    const double ki = K / (2.0 * T);
    const double kd = K * T / 2.0;

    u += kp * (e - e1) + ki * (e + e1) + kd * (e - 2 * e1 + e2);

    e2 = e1;
    e1 = e;
    e0 = e;

    return u;
}

double PID::getU() const {
    return u;
}
