#include <iostream>
#include "pid.h"
#include "model.h"

int main() {
    PID pid(2.0, 0.5, 0.1, 0.1);  // P, I, D, dt
    Model model;                  // y = 0 by default
    const double setpoint = 1.0;  // desired value
    const double dt = 0.1;        // simulation step

    for (int i = 0; i < 50; ++i) {
        double measured = model.getY();                 // current system value
        double control = pid.compute(setpoint, measured); // compute control signal
        double output = model.update(control, dt);        // apply control
        std::cout << "Step " << i
                  << " | Control: " << control
                  << " | Output: " << output
                  << std::endl;
    }

    return 0;
}
