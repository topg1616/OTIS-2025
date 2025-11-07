#ifndef PID_H
#define PID_H

#include <algorithm>

/**
 * @class PID
 * @brief Дискретный ПИД-регулятор.
 */
class PID {
private:
    double Kp = 0.0;          // Пропорциональный коэффициент
    double Ki = 0.0;          // Интегральный коэффициент
    double Kd = 0.0;          // Дифференциальный коэффициент
    double dt = 0.1;          // Шаг дискретизации (сек)
    double inv_dt = 10.0;     // 1/dt, для ускорения вычислений
    double prev_error = 0.0;  // Ошибка предыдущего шага
    double integral = 0.0;    // Интегральная ошибка
    double output_min = -1e9; // Минимальный выход
    double output_max = 1e9;  // Максимальный выход
    double integral_min = -1e6;
    double integral_max = 1e6;

public:
    explicit PID(double Kp_ = 0.0, double Ki_ = 0.0, double Kd_ = 0.0, double dt_ = 0.1) noexcept;

    double compute(double setpoint, double measured) noexcept;
    void reset() noexcept;

    void setOutputLimits(double min, double max) noexcept;
    void setIntegralLimits(double min, double max) noexcept;
};

#endif // PID_H
