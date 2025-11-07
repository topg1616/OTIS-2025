#include "pid.h"
#include <algorithm>

// Конструктор: только инициализация коэффициентов, остальные члены через in-class инициализаторы
PID::PID(double Kp_, double Ki_, double Kd_, double dt_) noexcept
    : Kp(Kp_), Ki(Ki_), Kd(Kd_), dt(dt_) {}

// Вычисление управляющего воздействия
double PID::compute(double setpoint, double measured) noexcept {
    double error = setpoint - measured;
    integral += error * dt;

    // Анти-виндап: ограничение интеграла
    if (integral > integral_max) integral = integral_max;
    if (integral < integral_min) integral = integral_min;

    double derivative = (error - prev_error) / dt;
    prev_error = error;

    double out = Kp * error + Ki * integral + Kd * derivative;

    // Ограничение выхода
    if (out > output_max) out = output_max;
    if (out < output_min) out = output_min;

    return out;
}

// Сброс интегральной и предыдущей ошибки
void PID::reset() noexcept {
    prev_error = 0.0;
    integral = 0.0;
}

// Установка ограничений выходного сигнала
void PID::setOutputLimits(double min, double max) noexcept {
    if (min > max) return; // некорректный ввод, игнорируем
    output_min = min;
    output_max = max;
}

// Установка ограничений интеграла
void PID::setIntegralLimits(double min, double max) noexcept {
    if (min > max) return; // некорректный ввод, игнорируем
    integral_min = min;
    integral_max = max;
}