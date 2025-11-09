#include "pid.h"
#include <algorithm>
#include <iostream>

// Конструктор
PID::PID(double Kp_, double Ki_, double Kd_, double dt_)
    : Kp(Kp_), Ki(Ki_), Kd(Kd_)
{
    if (dt_ <= 0.0) {
        std::cerr << "PID::PID: invalid dt <= 0, using DEFAULT_DT=" << DEFAULT_DT << "\n";
        dt = DEFAULT_DT; // ensure DEFAULT_DT > 0
    } else {
        dt = dt_;
    }
    inv_dt = 1.0 / dt;
}

// Вычисление сигнала управления
double PID::compute(double setpoint, double measured) noexcept {
    const double error = setpoint - measured;

    // Интегральная составляющая с анти-виндапом
    integral = std::clamp(integral + error * dt, integral_min, integral_max);

    // Дифференциальная составляющая (по ошибке)
    const double derivative = (error - prev_error) * inv_dt;
    prev_error = error;

    // Выход PID (с ограничением)
    const double output = Kp * error + Ki * integral + Kd * derivative;
    return std::clamp(output, output_min, output_max);
}

// Сброс состояния PID
void PID::reset() noexcept {
    prev_error = 0.0;
    integral = 0.0;
}

// Установка ограничений выхода
void PID::setOutputLimits(double min, double max) {
    if (min > max) {
        std::cerr << "PID::setOutputLimits ignored invalid limits: min > max\n";
        return;
    }
    output_min = min;
    output_max = max;
}

// Установка ограничений интеграла
void PID::setIntegralLimits(double min, double max) {
    if (min > max) {
        std::cerr << "PID::setIntegralLimits ignored invalid limits: min > max\n";
        return;
    }
    integral_min = min;
    integral_max = max;

    // Ограничиваем текущий интеграл под новые границы
    integral = std::clamp(integral, integral_min, integral_max);
}

// Изменение времени дискретизации
void PID::setDt(double new_dt) {
    if (new_dt <= 0.0) {
        std::cerr << "PID::setDt ignored invalid dt <= 0\n";
        return;
    }
    dt = new_dt;
    inv_dt = 1.0 / dt;
}
