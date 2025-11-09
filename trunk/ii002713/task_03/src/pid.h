#ifndef PID_H
#define PID_H

#include <limits>

/**
 * @class PID
 * @brief Proportional-Integral-Derivative (PID) controller class.
 *
 * Provides basic PID control functionality with configurable
 * proportional, integral, and derivative gains, as well as
 * output and integral clamping to prevent windup.
 */
class PID {
public:
    /**
     * @brief Construct a new PID controller.
     *
     * @param Kp_ Proportional gain.
     * @param Ki_ Integral gain.
     * @param Kd_ Derivative gain.
     * @param dt_ Sampling time (seconds). If non-positive, a default value is used.
     */
    explicit PID(double Kp_ = 0.0, double Ki_ = 0.0, double Kd_ = 0.0, double dt_ = DEFAULT_DT) noexcept;

    /**
     * @brief Compute the PID control output.
     *
     * @param setpoint Desired target value.
     * @param measured Current measured value.
     * @return Control signal after applying PID correction.
     */
    double compute(double setpoint, double measured) noexcept;

    /**
     * @brief Reset the PID internal state.
     *
     * Clears the accumulated integral term and previous error.
     */
    void reset() noexcept;

    /**
     * @brief Set output signal limits.
     *
     * @param min Lower limit for controller output.
     * @param max Upper limit for controller output.
     *
     * If min > max, the call is ignored and previous limits are preserved.
     */
    void setOutputLimits(double min, double max);

    /**
     * @brief Set integral term limits to prevent windup.
     *
     * @param min Lower limit for the integral term.
     * @param max Upper limit for the integral term.
     *
     * If min > max, the call is ignored and previous limits are preserved.
     */
    void setIntegralLimits(double min, double max);

    /**
     * @brief Change the controller sampling time.
     *
     * @param new_dt New sampling time in seconds.
     *
     * If new_dt <= 0, the change is ignored.
     */
    void setDt(double new_dt);

private:
    double Kp{};
    double Ki{};
    double Kd{};
    double dt{};
    double inv_dt{}; ///< Stores reciprocal of dt for faster derivative computation
    double prev_error{}; ///< Previous cycle error
    double integral{};   ///< Integrated error term

    double output_min{-1e9};
    double output_max{1e9};
    double integral_min{-1e6};
    double integral_max{1e6};

    static constexpr double DEFAULT_DT = 0.1;
};

#endif // PID_H
