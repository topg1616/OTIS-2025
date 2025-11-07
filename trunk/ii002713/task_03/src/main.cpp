#include <iostream>
#include "pid.h"
#include "model.h"

int main() {
    // Создаем PID с коэффициентами Kp=2.0, Ki=1.0, Kd=0.5, dt=0.1
    PID pid(2.0, 1.0, 0.5, 0.1);
    pid.setOutputLimits(-10.0, 10.0);      // Ограничение выхода
    pid.setIntegralLimits(-5.0, 5.0);      // Ограничение интеграла

    // Создаем модель с начальным состоянием y0=0.0
    Model model(0.0);

    const double setpoint = 1.0;   // Целевая точка
    const int steps = 50;           // Количество шагов симуляции

    std::cout << "Step\tOutput\tModel_y\n";

    for (int i = 0; i < steps; ++i) {
        double measured = model.getY();
        double control = pid.compute(setpoint, measured);
        model.update(control);  // Простая интеграционная модель y += u

        std::cout << i << "\t" 
                  << control << "\t" 
                  << model.getY() << "\n";
    }

    return 0;
}
