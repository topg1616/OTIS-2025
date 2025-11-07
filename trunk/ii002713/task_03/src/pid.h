#ifndef PID_H
#define PID_H

/**
 * @brief Simple PID controller class.
 *
 * Implements a discrete-time PID controller with anti-windup and output limits.
 */
class PID {
private:
    double Kp{0.0};
    double Ki{0.0};
    double Kd{0.0};
    double dt{0.1};
    double inv_dt{10.0};  // 1/dt for faster derivative calculation

    double prev_error{0.0};
    double integral{0.0};

    double output_min{-1e9};
    double output_max{1e9};
    double integral_min{-1e6};
    double integral_max{1e6};

public:
    explicit PID(double Kp_ = 0.0, double Ki_ = 0.0, double Kd_ = 0.0, double dt_ = 0.1) noexcept;

    /**
     * @brief Compute control signal
     * @param setpoint Desired value
     * @param measured Measured value
     * @return Control output
     */
    double compute(double setpoint, double measured) noexcept;

    /// Reset integral and previous error
    void reset() noexcept;

    /**
     * @brief Set output limits
     * @note If min > max, limits are not updated (silent failure)
     */
    void setOutputLimits(double min, double max) noexcept;

    /**
     * @brief Set integral limits (anti-windup)
     * @note If min > max, limits are not updated (silent failure)
     */
    void setIntegralLimits(double min, double max) noexcept;
};

#endif // PID_H
