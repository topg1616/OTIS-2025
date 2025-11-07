#include "pid.h"
#include <algorithm> // std::clamp

PID::PID(double Kp_, double Ki_, double Kd_, double dt_) noexcept
    : Kp(Kp_), Ki(Ki_), Kd(Kd_), dt(dt_), inv_dt(1.0 / dt_) {}

// Вычисление управляющего воздействия
double PID::compute(double setpoint, double measured) noexcept {
    double error = setpoint - measured;

    // Интеграл с ограничением (анти-виндап)
    integral += error * dt;
    integral = std::clamp(integral, integral_min, integral_max);

    // Производная
    double derivative = (error - prev_error) * inv_dt;
    prev_error = error;

    // ПИД-выход с ограничением
    double out = Kp * error + Ki * integral + Kd * derivative;
    out = std::clamp(out, output_min, output_max);

    return out;
}

// Сброс интегральной и предыдущей ошибки
void PID::reset() noexcept {
    prev_error = 0.0;
    integral = 0.0;
}

// Установка ограничений выхода
void PID::setOutputLimits(double min, double max) noexcept {
    if (min > max) return; // проверка валидности
    output_min = min;
    output_max = max;
}

// Установка ограничений интеграла
void PID::setIntegralLimits(double min, double max) noexcept {
    if (min > max) return; // проверка валидности
    integral_min = min;
    integral_max = max;
}
