#include "pid.h"
#include <algorithm>

PID::PID(double Kp_, double Ki_, double Kd_, double dt_) noexcept
    : Kp(Kp_), Ki(Ki_), Kd(Kd_), dt(dt_), prev_error(0.0), integral(0.0),
      output_min(-1e9), output_max(1e9), integral_min(-1e6), integral_max(1e6) {}

double PID::compute(double setpoint, double measured) noexcept {
    double error = setpoint - measured;
    integral += error * dt;

    // Анти-виндап: ограничиваем интеграл
    if (integral > integral_max) integral = integral_max;
    if (integral < integral_min) integral = integral_min;

    double derivative = (error - prev_error) / dt;
    prev_error = error;

    double out = Kp * error + Ki * integral + Kd * derivative;

    // Ограничиваем выход
    if (out > output_max) out = output_max;
    if (out < output_min) out = output_min;

    return out;
}

void PID::reset() noexcept {
    prev_error = 0.0;
    integral = 0.0;
}

void PID::setOutputLimits(double min, double max) noexcept {
    output_min = min;
    output_max = max;
}

void PID::setIntegralLimits(double min, double max) noexcept {
    integral_min = min;
    integral_max = max;
}
