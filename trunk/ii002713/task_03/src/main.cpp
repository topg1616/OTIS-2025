#include <iostream>
#include "pid.h"
#include "model.h"

int main() {
    PID pid(2.0, 0.5, 0.1, 0.1);  // P, I, D, dt
    Model model;                  // y = 0 по умолчанию
    const double setpoint = 1.0;  // желаемое значение
    const double dt = 0.1;        // шаг моделирования

    for (int i = 0; i < 50; ++i) {
        double measured = model.getY();                 // текущее значение системы
        double control = pid.compute(setpoint, measured); // вычислить управляющее воздействие
        double output = model.update(control, dt);        // применить воздействие
        std::cout << "Step " << i
                  << " | Control: " << control
                  << " | Output: " << output
                  << std::endl;
    }

    return 0;
}
