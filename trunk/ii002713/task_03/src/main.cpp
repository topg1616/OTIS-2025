#include <iostream>
#include "pid.h"
#include "model.h"

int main() {
    PID pid(2.0, 1.0, 0.05, 0.1); // Kp, Ki, Kd, dt
    pid.setOutputLimits(-10.0, 10.0);
    pid.setIntegralLimits(-5.0, 5.0);

    Model model;
    const double setpoint = 1.0;

    for (int i = 0; i < 50; ++i) {
        double measured = model.getY();
        double u = pid.compute(setpoint, measured);
        model.update(u);
        std::cout << "Step " << i << ": y = " << model.getY() << ", u = " << u << std::endl;
    }

    return 0;
}
