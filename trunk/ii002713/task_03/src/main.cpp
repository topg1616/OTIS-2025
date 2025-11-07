#include <iostream>
#include "pid.h"
#include "model.h"

/**
 * @brief Точка входа в программу.
 *
 * Выполняет моделирование замкнутой системы «ПИД-регулятор – объект управления».
 * Печатает изменение выходного сигнала по шагам.
 *
 * @return Код завершения программы.
 */
int main() {
    PID pid(2.0, 1.0, 0.1);  // ПИД-регулятор с параметрами K=2.0, T=1.0, dt=0.1
    Model model;             // Модель управляемого объекта

    const double setpoint = 1.0;  // Желаемое значение выхода
    double time = 0.0;            // Текущее время
    const double dt = 0.1;        // Шаг интегрирования
    const int steps = 100;        // Количество итераций моделирования

    std::cout << "Time\tOutput\n";

    for (int i = 0; i < steps; ++i) {
        double y = model.getOutput();
        double error = setpoint - y;
        double u = pid.compute(error);
        model.update(u, dt);

        std::cout << time << "\t" << y << "\n";
        time += dt;
    }

    return 0;
}
