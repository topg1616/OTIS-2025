#ifndef PID_H
#define PID_H

#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Класс дискретного ПИД-регулятора.
 * 
 * Используется инкрементная форма:
 * \f[
 * \Delta u(k) = q_0 e(k) + q_1 e(k-1) + q_2 e(k-2)
 * \f]
 */
class PID {
private:
    double K;   ///< Коэффициент усиления
    double T;   ///< Время интегрирования
    double TD;  ///< Время дифференцирования
    double T0;  ///< Шаг дискретизации

    double q0, q1, q2; ///< Коэффициенты дискретного регулятора

    double e0, e1, e2; ///< Ошибки e(k), e(k-1), e(k-2)
    double u;          ///< Текущее управляющее воздействие

public:
    /**
     * @brief Конструктор ПИД-регулятора.
     * @param K_ Коэффициент усиления.
     * @param T_ Время интегрирования.
     * @param TD_ Время дифференцирования.
     * @param T0_ Шаг дискретизации.
     */
    PID(double K_ = 1.0, double T_ = 1.0, double TD_ = 0.0, double T0_ = 1.0);

    /**
     * @brief Вычислить новое управляющее воздействие.
     * @param y Выход системы.
     * @param yzad Заданное значение (уставка).
     * @return Новое управляющее воздействие.
     */
    double compute(double y, double yzad);

    /**
     * @brief Сброс состояния регулятора.
     */
    void reset();
};

#endif