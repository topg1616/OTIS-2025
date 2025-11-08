#include "pid.h"
#include <algorithm> // std::clamp

/**
 * @brief Construct a PID controller.
 *
 * Validates the time step and initializes internal state.
 */
PID::PID(double Kp_, double Ki_, double Kd_, double dt_) noexcept
    : Kp(Kp_), Ki(Ki_), Kd(Kd_), prev_error(0.0), integral(0.0)
{
    if (dt_ <= 0.0) {
    dt = DEFAULT_DT;
    }
    else {dt = dt_;}
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

    integral = std::clamp(integral + error * dt, integral_min, integral_max);

    double derivative = (error - prev_error) * inv_dt;
    prev_error = error;

    return std::clamp(Kp * error + Ki * integral + Kd * derivative, output_min, output_max);
}

/**
 * @brief Reset the PID controller.
 *
 * Clears the integral and previous error.
 */
void PID::reset() noexcept
{
    prev_error = 0.0;
    integral = 0.0;
}

/**
 * @brief Set output limits.
 *
 * @param min Minimum output
 * @param max Maximum output
 */
void PID::setOutputLimits(double min, double max) noexcept
{
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
void PID::setIntegralLimits(double min, double max) noexcept
{
    if (min > max) {
        std::cerr << "PID::setIntegralLimits ignored invalid limits: min > max\n";
        return;
    }
    integral_min = min;
    integral_max = max;

    // Ensure current integral respects new bounds
    integral = std::clamp(integral, integral_min, integral_max);
}
