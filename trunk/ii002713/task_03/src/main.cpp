#include <iostream>
#include "pid.h"
#include "model.h"

int main() {
    // Создаём PID-контроллер
    PID pid(2.0, 1.0, 0.1, 0.1);  // Kp, Ki, Kd, dt
    pid.setOutputLimits(-10.0, 10.0);     // ограничение управляющего воздействия
    pid.setIntegralLimits(-5.0, 5.0);     // ограничение интеграла (антивиндап)

    // Создаём модель системы
    Model model(0.0);  // начальное состояние y = 0.0

    const double setpoint = 1.0;  // желаемое значение
    const int steps = 50;         // число шагов симуляции

    std::cout << "Step\tY\tControl\n";

    for (int i = 0; i < steps; ++i) {
        double measured = model.getY();
        double u = pid.compute(setpoint, measured); // вычисление управляющего воздействия
        model.update(u);                             // обновление состояния модели

        std::cout << i << "\t" << measured << "\t" << u << "\n";
    }

    std::cout << "Final state: y = " << model.getY() << "\n";

    return 0;
}
