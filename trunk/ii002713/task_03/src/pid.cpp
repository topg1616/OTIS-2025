#include "pid.h"
#include <algorithm> // std::clamp

PID::PID(double Kp_, double Ki_, double Kd_, double dt_) noexcept
    : Kp(Kp_), Ki(Ki_), Kd(Kd_), dt(dt_), inv_dt(1.0 / dt_) {}

// Compute control signal
double PID::compute(double setpoint, double measured) noexcept {
    double error = setpoint - measured;

    integral += error * dt;
    integral = std::clamp(integral, integral_min, integral_max); // anti-windup

    double derivative = (error - prev_error) * inv_dt;
    prev_error = error;

    double out = Kp * error + Ki * integral + Kd * derivative;
    out = std::clamp(out, output_min, output_max);

    return out;
}

// Reset integral and previous error
void PID::reset() noexcept {
    prev_error = 0.0;
    integral = 0.0;
}

// Set output limits
void PID::setOutputLimits(double min, double max) noexcept {
    if (min > max) return; // silent failure documented in header
    output_min = min;
    output_max = max;
}

// Set integral limits
void PID::setIntegralLimits(double min, double max) noexcept {
    if (min > max) return; // silent failure documented in header
    integral_min = min;
    integral_max = max;
}
