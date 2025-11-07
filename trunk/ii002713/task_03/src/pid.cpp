#include "pid.h"

PID::PID(double k, double t, double delta_t)
    : K(k), T(t), dt(delta_t), e0(0.0), e1(0.0), e2(0.0), u(0.0) {}

double PID::compute(double e) {
    e2 = e1;
    e1 = e0;
    e0 = e;

    // Дискретная реализация ПИД-регулятора (позиционная форма)
    double de = e0 - e1;
    double ie = e0 + e1 + e2;
    u += K * (de + (dt / T) * ie);

    return u;
}
