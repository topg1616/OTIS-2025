#include "pid.h"

// Конструктор ПИД-регулятора
PID::PID(double Kp_, double Ki_, double Kd_, double dt_) noexcept
    : Kp(Kp_), Ki(Ki_), Kd(Kd_), dt(dt_) {
    inv_dt = 1.0 / dt;
}

// Вычисление управляющего воздействия
double PID::compute(double setpoint, double measured) noexcept {
    double error = setpoint - measured;

    // Интегральная часть
    integral += error * dt;
    if (integral > integral_max) integral = integral_max;
    else if (integral < integral_min) integral = integral_min;

    // Производная часть
    double derivative = (error - prev_error) * inv_dt;
    prev_error = error;

    // Суммарный выход
    double out = Kp * error + Ki * integral + Kd * derivative;
    if (out > output_max) out = output_max;
    else if (out < output_min) out = output_min;

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
