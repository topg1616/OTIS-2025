#include "model.h"
#include <iostream>
#include <cmath>

/**
 * Линейная модель.
 *
 * Вычисляет выход y линейной системы по формуле:
 * y_next = a * y + b * u
 *
 * @param a  Параметр модели.
 * @param b  Параметр модели.
 * @param u  Входной сигнал.
 * @param y  Предыдущее значение выхода.
 * @return   Новое значение выхода y.
 */
double Linear(double a, double b, double u, double y) {
    return a * y + b * u;
}

/**
 * Симуляция линейной модели.
 *
 * Функция выполняет пошаговую симуляцию линейной системы.
 *
 * @param a      Параметр модели.
 * @param b      Параметр модели.
 * @param u      Входной сигнал на каждом шаге симуляции.
 * @param steps  Количество шагов симуляции.
 *
 * Поведение:
 * - Инициализирует текущее значение y нулём.
 * - На каждом шаге вычисляет новое значение y с помощью функции Linear().
 * - Выводит текущее значение y на каждом шаге.
 */
void simulateLinear(double a, double b, double u, int steps) {
    std::cout << "Linear model" << '\n';
    double y = 0.0;
    for (int i = 0; i < steps; ++i) {
        std::cout << "Step " << i << ": " << y << '\n';
        y = Linear(a, b, u, y);
    }
    std::cout << '\n';
}

/**
 * Нелинейная модель.
 *
 * Вычисляет выход y нелинейной системы по формуле:
 * y_next = a * y - b * yPrev^2 + c * u + d * sin(uPrev)
 *
 * @param p      Структура NonlinearParams, содержащая параметры модели (a, b, c, d).
 * @param u      Текущий входной сигнал.
 * @param uPrev  Предыдущий входной сигнал.
 * @param y      Текущее значение выхода.
 * @param yPrev  Предыдущее значение выхода.
 * @return       Новое значение выхода y.
 */
double Nonlinear(const NonlinearParams& p, double u, double uPrev, double y, double yPrev) {
    return p.a * y - p.b * (yPrev * yPrev) + p.c * u + p.d * std::sin(uPrev);
}

/**
 * Симуляция нелинейной модели.
 *
 * Функция выполняет пошаговую симуляцию нелинейной системы.
 *
 * @param p      Структура NonlinearParams, содержащая параметры модели (a, b, c, d).
 * @param u      Входной сигнал на каждом шаге симуляции.
 * @param steps  Количество шагов симуляции.
 *
 * Поведение:
 * - Инициализирует текущие и предыдущие состояния y и u.
 * - На каждом шаге вычисляет новое значение y с помощью функции Nonlinear().
 * - Выводит текущее значение y на каждом шаге.
 * - Обновляет предыдущие значения yPrev и uPrev для следующего шага.
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
