#include "pid.h"
#include <algorithm> // std::clamp
#include <iostream>  // std::cerr

/**
 * @brief Construct a PID controller.
 *
 * Validates the time step and initializes internal state.
 */
PID::PID(double Kp_, double Ki_, double Kd_, double dt_) noexcept
    : Kp(Kp_), Ki(Ki_), Kd(Kd_), prev_error(0.0), integral(0.0)
{
    if (dt_ <= 0.0) {
        std::cerr << "PID::PID: invalid dt <= 0, using DEFAULT_DT\n";
        dt = DEFAULT_DT;
    } else {
        dt = dt_;
    }

    inv_dt = 1.0 / dt;
}

/**
 * @brief Compute the PID control signal.
 *
 * @param setpoint Desired value
 * @param measured Measured value
 * @return Control output
 */
double PID::compute(double setpoint, double measured) noexcept {
    double error = setpoint - measured;

    // Integral term with anti-windup
    integral += error * dt;
    integral = std::clamp(integral, integral_min, integral_max);

    // Derivative term (safe, since inv_dt is initialized)
    double derivative = (error - prev_error) * inv_dt;
    prev_error = error;

    // PID output
    double output = Kp * error + Ki * integral + Kd * derivative;
    return std::clamp(output, output_min, output_max);
}

/**
 * @brief Reset the PID controller.
 *
 * Clears the integral and previous error.
 */
void PID::reset() noexcept {
    prev_error = 0.0;
    integral = 0.0;
}

/**
 * @brief Set output limits.
 *
 * @param min Minimum output
 * @param max Maximum output
 */
void PID::setOutputLimits(double min, double max) noexcept {
    if (min > max) {
        std::cerr << "PID::setOutputLimits ignored invalid limits: min > max\n";
        return;
    }
    output_min = min;
    output_max = max;
}

/**
 * @brief Set integral limits.
 *
 * @param min Minimum integral
 * @param max Maximum integral
 */
void PID::setIntegralLimits(double min, double max) noexcept {
    if (min > max) {
        std::cerr << "PID::setIntegralLimits ignored invalid limits: min > max\n";
        return;
    }

    integral_min = min;
    integral_max = max;

    // Clamp current integral to new bounds
    integral = std::clamp(integral, integral_min, integral_max);
}
