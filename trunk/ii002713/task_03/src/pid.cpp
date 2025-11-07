#include "pid.h"
#include <algorithm> // std::clamp
#include <iostream>  // std::cerr

PID::PID(double Kp_, double Ki_, double Kd_, double dt_) noexcept
    : Kp(Kp_), Ki(Ki_), Kd(Kd_), dt(dt_) {
    if (dt_ <= 0.0) {
        std::cerr << "PID::PID: invalid dt <= 0, using DEFAULT_DT\n";
        dt = PID::DEFAULT_DT;
    } else {
        dt = dt_;
    }
    inv_dt = 1.0 / dt;
}

// Compute control signal
double PID::compute(double setpoint, double measured) noexcept {
    double error = setpoint - measured;

    // Integral term (anti-windup)
    integral += error * dt;
    integral = std::clamp(integral, integral_min, integral_max);

    // Derivative term
    double derivative = (error - prev_error) * inv_dt;
    prev_error = error;

    // PID output with clamping
    double out = Kp * error + Ki * integral + Kd * derivative;
    out = std::clamp(out, output_min, output_max);

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

    // ensure current integral respects new bounds
    integral = std::clamp(integral, integral_min, integral_max);
}
