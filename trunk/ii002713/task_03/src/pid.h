#ifndef PID_H
#define PID_H

class PID {
private:
    double Kp{};
    double Ki{};
    double Kd{};
    double dt{};
    double inv_dt{}; // хранит 1/dt для оптимизации вычислений
    double prev_error{}; // предыдущая ошибка
    double integral{};   // интеграл ошибки

    double output_min{-1e9};
    double output_max{1e9};
    double integral_min{-1e6};
    double integral_max{1e6};

    static constexpr double DEFAULT_DT = 0.1;

public:
    explicit PID(double Kp_ = 0.0, double Ki_ = 0.0, double Kd_ = 0.0, double dt_ = DEFAULT_DT) noexcept;

    double compute(double setpoint, double measured) noexcept;
    void reset() noexcept;

    /**
     * @brief Set output limits
     * @param min Minimum output
     * @param max Maximum output
     * @note If min > max, limits are not updated
     */
    void setOutputLimits(double min, double max) noexcept;

    /**
     * @brief Set integral limits (anti-windup)
     * @param min Minimum integral
     * @param max Maximum integral
     * @note If min > max, limits are not updated
     */
    void setIntegralLimits(double min, double max) noexcept;
};

#endif // PID_H
