#include "pid.h"
#include "model.h"
#include <iostream>
#include <vector>

int main() {
    // Настройка PID контроллера: Kp, Ki, Kd
    PID pid(2.0, 1.0, 0.1, 0.1);

    // Ограничения выхода и интеграла
    pid.setOutputLimits(-10.0, 10.0);
    pid.setIntegralLimits(-5.0, 5.0);

    // Создаем модель с начальным состоянием y = 0
    Model model(0.0);

    const double setpoint = 1.0;  // Желаемое значение
    const int steps = 50;          // Количество шагов симуляции
    std::vector<double> history;   // Для хранения состояния модели

    for (int i = 0; i < steps; ++i) {
        double y = model.getY();
        double u = pid.compute(setpoint, y); // Сигнал управления
        model.update(u);                     // Обновляем модель
        history.push_back(model.getY());

        std::cout << "Step " << i
                  << ", y = " << model.getY()
                  << ", control = " << u
                  << std::endl;
    }

    std::cout << "\nFinal model output: " << model.getY() << std::endl;
    return 0;
}
