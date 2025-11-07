#ifndef PID_H
#define PID_H

/**
 * @class PID
 * @brief Discrete-time PID controller with anti-windup and output limits.
 *
 * Provides a simple PID controller:
 *   u = Kp*e + Ki*integral(e) + Kd*derivative(e)
 *
 * The class stores internal state (integral, previous error). Use reset()
 * to clear state. Limits for output and integral can be set via the
 * corresponding setters.
 */
class PID {
private:
    double Kp{};           ///< proportional gain
    double Ki{};           ///< integral gain
    double Kd{};           ///< derivative gain
    double dt{};           ///< time step (s)
    double inv_dt{};       ///< 1/dt for faster derivative calculation

    double prev_error{};   ///< previous error (for derivative)
    double integral{};     ///< accumulated integral

    double output_min{-1e9};   ///< minimum allowed output
    double output_max{1e9};    ///< maximum allowed output
    double integral_min{-1e6}; ///< minimum allowed integral
    double integral_max{1e6};  ///< maximum allowed integral

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
     * @param measured current measured value
     * @return control signal u
     */
    double compute(double setpoint, double measured) noexcept;

    /**
     * @brief Reset internal state (integral and previous error).
     */
    void reset() noexcept;

    /**
     * @brief Set output limits.
     * @param min minimum allowed output
     * @param max maximum allowed output
     * @note If min > max this function does not update the limits and writes
     *       a warning to stderr (no exception is thrown).
     */
    void setOutputLimits(double min, double max) noexcept;

    /**
     * @brief Set integral limits (anti-windup).
     * @param min minimum allowed integral
     * @param max maximum allowed integral
     * @note If min > max this function does not update the limits and writes
     *       a warning to stderr (no exception is thrown).
     */
    void setIntegralLimits(double min, double max) noexcept;
};

#endif // PID_H
