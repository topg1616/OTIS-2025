#ifndef PID_H
#define PID_H

#include <limits>

/**
 * @class PID
 * @brief Proportional-Integral-Derivative (PID) controller class.
 *
 * Provides basic PID control functionality with configurable gains,
 * output limits, and integral anti-windup protection.
 */
class PID {
public:
    /**
     * @brief Constructs a PID controller with given coefficients and time step.
     * @param Kp_ Proportional gain.
     * @param Ki_ Integral gain.
     * @param Kd_ Derivative gain.
     * @param dt_ Sampling time step (must be > 0).
     */
    explicit PID(double Kp_ = 0.0, double Ki_ = 0.0, double Kd_ = 0.0, double dt_ = DEFAULT_DT);

    /**
     * @brief Computes the control signal based on setpoint and measured value.
     * @param setpoint Desired target value.
     * @param measured Current measured process value.
     * @return Computed control signal (clamped within output limits).
     */
    double compute(double setpoint, double measured) noexcept;

    /**
     * @brief Resets the controller’s internal state (integral and previous error).
     */
    void reset() noexcept;

    /**
     * @brief Sets the output limits for the control signal.
     * @param min Minimum output value.
     * @param max Maximum output value.
     */
    void setOutputLimits(double min, double max);

    /**
     * @brief Sets the limits for the integral term to prevent windup.
     * @param min Minimum integral value.
     * @param max Maximum integral value.
     */
    void setIntegralLimits(double min, double max);

    /**
     * @brief Sets the sampling time (dt) for the PID controller.
     * @param new_dt New time step (must be > 0).
     */
    void setDt(double new_dt);

private:
    double Kp;
    double Ki;
    double Kd;

    double dt;
    double inv_dt;

    double prev_error = 0.0;
    double integral = 0.0;

    double output_min = -std::numeric_limits<double>::infinity();
    double output_max =  std::numeric_limits<double>::infinity();
    double integral_min = -std::numeric_limits<double>::infinity();
    double integral_max =  std::numeric_limits<double>::infinity();

    static constexpr double DEFAULT_DT = 0.01;
};

#endif // PID_H
