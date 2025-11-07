#include "pid.h"
#include <algorithm> // std::clamp
#include <iostream>  // std::cerr for warnings

PID::PID(double Kp_, double Ki_, double Kd_, double dt_) noexcept
    : Kp(Kp_), Ki(Ki_), Kd(Kd_), dt(dt_), inv_dt(1.0 / dt_) {}

// Compute control signal
double PID::compute(double setpoint, double measured) noexcept {
    double error = setpoint - measured;

    // Integral term with anti-windup
    integral += error * dt;
    if (integral > integral_max) integral = integral_max;
    else if (integral < integral_min) integral = integral_min;

    // Derivative term (use inv_dt for performance)
    double derivative = (error - prev_error) * inv_dt;
    prev_error = error;

    double out = Kp * error + Ki * integral + Kd * derivative;

    // Output limits (clamping)
    if (out > output_max) out = output_max;
    else if (out < output_min) out = output_min;

    return out;
}

void PID::reset() noexcept {
    prev_error = 0.0;
    integral = 0.0;
}

void PID::setOutputLimits(double min, double max) noexcept {
    if (min > max) {
        std::cerr << "PID::setOutputLimits ignored invalid limits: min > max\n";
        return;
    }
    output_min = min;
    output_max = max;
}

void PID::setIntegralLimits(double min, double max) noexcept {
    if (min > max) {
        std::cerr << "PID::setIntegralLimits ignored invalid limits: min > max\n";
        return;
    }
    integral_min = min;
    integral_max = max;
}
