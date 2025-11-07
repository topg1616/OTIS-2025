#ifndef MODEL_H
#define MODEL_H

#include <cmath>

/**
 * @brief Класс математической модели системы.
 */
class Model {
private:
    double y = 0.0; //Текущее значение выходного сигнала

public:
    explicit Model(double y0); //Конструктор с начальным значением

    /**
     * @brief Возвращает текущее значение выхода.
     */
    double getY() const;

    /**
     * @brief Обновляет состояние модели.
     * @param u Управляющее воздействие
     */
    void update(double u);
};

#endif
