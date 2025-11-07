#include <iostream>
#include <iomanip>
#include "model.h"
#include "pid.h"

int main() {
    double setpoint = 10.0;    // Желаемое значение
    PID pid(0.5, 0.1);         // Коэффициенты регулятора
    Model model(0.0);          // Начальное состояние модели

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Step\tControl (u)\tOutput (y)\tError\n";

    for (int step = 0; step < 50; ++step) {
        double error = setpoint - model.getY(); // ошибка
        double control = pid.compute(error);    // сигнал управления
        model.update(control);                  // реакция модели

        std::cout << step << "\t" 
                  << control << "\t\t" 
                  << model.getY() << "\t\t" 
                  << error << "\n";
    }

    std::cout << "\nFinal output y ≈ " << model.getY() 
              << " (target = " << setpoint << ")\n";

    return 0;
}
