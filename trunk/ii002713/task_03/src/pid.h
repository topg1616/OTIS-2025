#ifndef PID_H
#define PID_H

#include <limits> // для infinity()

/**
 * @class PID
 * @brief Proportional-Integral-Derivative (PID) controller class.
 *
 * This class implements a discrete-time PID controller for process control applications.
 * It allows configuration of proportional, integral, and derivative gains, as well as
 * output and integral windup limits. The controller can be used to compute control
 * signals based on a setpoint and measured process variable.
 */
class PID {
public:
    /**
     * @brief Constructs a PID controller with the specified gains and timestep.
     * @param Kp_ Proportional gain.
     * @param Ki_ Integral gain.
     * @param Kd_ Derivative gain.
     * @param dt_ Discrete time step (seconds).
     */
    PID(double Kp_, double Ki_, double Kd_, double dt_) noexcept;

    /**
     * @brief Computes the PID control signal.
     * @param setpoint The desired target value.
     * @param measured The current measured value.
     * @return The computed control output.
     */
    double compute(double setpoint, double measured) noexcept;

    /**
     * @brief Resets the internal state of the PID controller (integral and previous error).
     */
    void reset() noexcept;

    /**
     * @brief Sets the minimum and maximum output limits for the controller.
     * @param min Minimum output value.
     * @param max Maximum output value.
     */
    void setOutputLimits(double min, double max) noexcept;

    /**
     * @brief Sets the minimum and maximum limits for the integral term (anti-windup).
     * @param min Minimum integral value.
     * @param max Maximum integral value.
     */
    void setIntegralLimits(double min, double max) noexcept;

    /**
     * @brief Sets a new discrete time step for the controller.
     * @param new_dt New time step (seconds).
     */
    void setDt(double new_dt) noexcept;

private:
    double Kp;
    double Ki;
    double Kd;

    double dt;
    double inv_dt;

    double prev_error = 0.0;  ///< Previous error term
    double integral   = 0.0;  ///< Integrated error term

    double output_min    = -std::numeric_limits<double>::infinity();
    double output_max    =  std::numeric_limits<double>::infinity();
    double integral_min  = -std::numeric_limits<double>::infinity();
    double integral_max  =  std::numeric_limits<double>::infinity();

    static constexpr double DEFAULT_DT = 0.01; ///< Default timestep (s)
};

#endif // PID_H
