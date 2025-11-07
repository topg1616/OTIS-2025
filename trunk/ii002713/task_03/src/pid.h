#ifndef PID_H
#define PID_H

#include <cmath>

/**
 * @brief Класс PID-регулятора.
 */
class PID {
private:
    double K = 1.0;   // Коэффициент усиления
    double T = 1.0;   // Постоянная времени
    double u = 0.0;   // Управляющее воздействие
    double e0 = 0.0;  // Текущая ошибка
    double e1 = 0.0;  // Ошибка на предыдущем шаге
    double e2 = 0.0;  // Ошибка два шага назад

public:
    explicit PID(double k, double t);

    /**
     * @brief Вычисляет управляющее воздействие по текущей ошибке.
     * @param e Ошибка регулирования
     * @return Новое значение управляющего воздействия
     */
    double compute(double e);

    /**
     * @brief Возвращает последнее значение управляющего воздействия.
     */
    double getU() const;
};

#endif
