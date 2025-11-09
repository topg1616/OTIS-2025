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
    explicit PID(double Kp_ = 0.0, double Ki_ = 0.0, double Kd_ = 0.0, double dt_ = DEFAULT_DT);

    double compute(double setpoint, double measured) noexcept;
    void reset() noexcept;
    void setOutputLimits(double min, double max);
    void setIntegralLimits(double min, double max);
    void setDt(double new_dt);

private:
    double Kp;
    double Ki;
    double Kd;

    double dt;
    double inv_dt;

    double prev_error = 0.0;
    double integral = 0.0;
    bool prev_error_initialized = false;

    double output_min = -std::numeric_limits<double>::infinity();
    double output_max =  std::numeric_limits<double>::infinity();
    double integral_min = -std::numeric_limits<double>::infinity();
    double integral_max =  std::numeric_limits<double>::infinity();

    static constexpr double DEFAULT_DT = 0.01;
};

#endif // PID_H
