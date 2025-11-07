#ifndef PID_H
#define PID_H

/**
 * @class PID
 * @brief Discrete-time PID controller with anti-windup and configurable limits.
 *
 * Formula:
 *   u = Kp * e + Ki * integral(e) + Kd * derivative(e)
 *
 * The controller keeps internal state (integral, previous error).
 * Use reset() to clear state between runs.
 */
class PID {
private:
    double Kp{0.0};        ///< proportional gain
    double Ki{0.0};        ///< integral gain
    double Kd{0.0};        ///< derivative gain
    double dt{0.1};        ///< time step (s)
    double inv_dt{10.0};   ///< 1/dt for efficient derivative computation

    double prev_error{0.0};///< previous error
    double integral{0.0};  ///< accumulated integral

    double output_min{-1e9};
    double output_max{1e9};
    double integral_min{-1e6};
    double integral_max{1e6};

    static constexpr double DEFAULT_DT = 0.1;

public:
    /**
     * @brief Construct a PID controller.
     * @param Kp_ proportional gain
     * @param Ki_ integral gain
     * @param Kd_ derivative gain
     * @param dt_ time step in seconds (default DEFAULT_DT)
     */
    explicit PID(double Kp_ = 0.0, double Ki_ = 0.0, double Kd_ = 0.0, double dt_ = DEFAULT_DT) noexcept;

    /**
     * @brief Compute control output for given setpoint and measurement.
     * @param setpoint desired value
     * @param measured measured value
     * @return control output u
     */
    double compute(double setpoint, double measured) noexcept;

    /**
     * @brief Reset internal state (integral and previous error).
     */
    void reset() noexcept;

    /**
     * @brief Set output limits.
     * @param min minimum output
     * @param max maximum output
     * @note If min > max this function does not update the limits and writes a warning to stderr.
     */
    void setOutputLimits(double min, double max) noexcept;

    /**
     * @brief Set integral limits (anti-windup).
     * @param min minimum integral
     * @param max maximum integral
     * @note If min > max this function does not update the limits and writes a warning to stderr.
     */
    void setIntegralLimits(double min, double max) noexcept;
};

#endif // PID_H
