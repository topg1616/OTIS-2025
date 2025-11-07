#ifndef PID_H
#define PID_H

#include <algorithm> // std::clamp
#include <iostream>  // std::cerr

/**
 * @brief PID controller class.
 *
 * Implements a discrete-time PID controller with anti-windup
 * and configurable output/integral limits.
 */
class PID {
private:
    double Kp{};          ///< Proportional gain
    double Ki{};          ///< Integral gain
    double Kd{};          ///< Derivative gain
    double dt{};          ///< Time step
    double inv_dt{};      ///< Stores 1/dt for optimization
    double prev_error{};  ///< Previous error
    double integral{};    ///< Integral of the error

    double output_min{-1e9}; ///< Minimum output
    double output_max{1e9};  ///< Maximum output
    double integral_min{-1e6}; ///< Minimum integral
    double integral_max{1e6};  ///< Maximum integral

    static constexpr double DEFAULT_DT = 0.1; ///< Default time step

public:
    /**
     * @brief Construct a PID controller.
     * @param Kp_ Proportional gain
     * @param Ki_ Integral gain
     * @param Kd_ Derivative gain
     * @param dt_ Time step (default 0.1s)
     */
    explicit PID(double Kp_ = 0.0, double Ki_ = 0.0, double Kd_ = 0.0, double dt_ = DEFAULT_DT) noexcept;

    /**
     * @brief Compute control signal based on setpoint and measurement.
     * @param setpoint Desired value
     * @param measured Measured value
     * @return Control output
     */
    double compute(double setpoint, double measured) noexcept;

    /**
     * @brief Reset integral and previous error.
     */
    void reset() noexcept;

    /**
     * @brief Set output limits.
     * @param min Minimum output
     * @param max Maximum output
     */
    void setOutputLimits(double min, double max) noexcept;

    /**
     * @brief Set integral limits.
     * @param min Minimum integral
     * @param max Maximum integral
     */
    void setIntegralLimits(double min, double max) noexcept;
};

#endif // PID_H
