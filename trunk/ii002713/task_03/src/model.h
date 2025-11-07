#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Класс, описывающий математическую модель объекта управления.
 * 
 * Модель основана на линейном звене первого порядка:
 * \f[
 * y(k+1) = a_1 \cdot y(k) + b_1 \cdot u(k)
 * \f]
 */
class Model {
private:
    double a1; ///< Коэффициент обратной связи
    double b1; ///< Коэффициент усиления
    double y;  ///< Текущее значение выхода

public:
    /**
     * @brief Конструктор модели.
     * @param a1_ Коэффициент обратной связи.
     * @param b1_ Коэффициент усиления.
     */
    Model(double a1_ = 0.9, double b1_ = 0.1);

    /**
     * @brief Выполнить один шаг моделирования.
     * @param u Управляющее воздействие.
     * @return Новое значение выхода системы.
     */
    double step(double u);

    /**
     * @brief Получить текущее значение выхода системы.
     */
    double getY() const;

    /**
     * @brief Сбросить состояние модели.
     * @param value Новое значение выхода.
     */
    void reset(double value = 0.0);
};

#endif
