#include <iostream>
#include "pid.h"
#include "model.h"

int main() {
    PID pid(2.0, 0.5, 0.1, 0.1); // Пропорциональный, интегральный, дифференциальный коэффициенты
    Model model;                 // Модель с выходом y = 0
    const double setpoint = 1.0; // Цель (желаемое значение)

    for (int i = 0; i < 50; ++i) {
        double measured = model.getY();           // Текущее значение
        double control = pid.compute(setpoint, measured); // Рассчитать управляющее воздействие
        model.update(control);                    // Применить его к модели
        std::cout << "Step " << i 
                  << " | Control: " << control 
                  << " | Output: " << model.getY() 
                  << std::endl;
    }

    return 0;
}
