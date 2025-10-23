#include "model.h"
#include <iostream>
#include <cmath>

// линейная модель
double Linear(double a, double b, double u, double y) {
    return a * y + b * u;
}

// симуляция линейной модели
void simulateLinear(double a, double b, double u, int steps) {
    std::cout << "Linear model" << '\n';
    double y = 0.0;
    for (int i = 0; i < steps; ++i) {
        std::cout << "Step " << i << ": " << y << '\n';
        y = Linear(a, b, u, y);
    }
    std::cout << '\n';
}

// нелинейная модель
double Nonlinear(const NonlinearParams& p, double u, double uPrev, double y, double yPrev) {
    return p.a * y - p.b * (yPrev * yPrev) + p.c * u + p.d * std::sin(uPrev);
}

/*
 Симуляция нелинейной модели.
 Функция выполняет пошаговую симуляцию нелинейной системы.

 param p      Структура NonlinearParams, содержащая параметры модели (a, b, c, d).
 param u      Входной сигнал на каждом шаге симуляции.
 param steps  Количество шагов симуляции.

 Поведение:
  - Инициализирует текущие и предыдущие состояния y и u.
  - На каждом шаге вычисляет новое значение y с помощью функции Nonlinear().
  - Выводит текущее значение y на каждом шаге.
  - Обновляет предыдущие значения yPrev и uPrev для следующего шага.
 */
void simulateNonlinear(const NonlinearParams& p, double u, int steps) {
    std::cout << "Nonlinear model" << '\n';
    double y = 0.0;
    double yPrev = 0.0;
    double uPrev = 0.0;
    for (int i = 0; i < steps; ++i) {
        std::cout << "Step " << i << ": " << y << '\n';
        double yNext = Nonlinear(p, u, uPrev, y, yPrev);
        yPrev = y;
        uPrev = u;
        y = yNext;
    }
    std::cout << '\n';
}