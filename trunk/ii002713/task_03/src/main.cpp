#include "pid.h"
#include <iostream>

// Linear model
double linearModel(double input) {
    constexpr double T = 0.05;
    return input * T;
}

// Nonlinear model
double nonlinearModel(double input) {
    constexpr double T = 0.05;
    return input * T + 0.01 * input * input;
}

void runSimulation(double (*model)(double), int steps, PID& controller, const std::string& name) {
    std::cout << "=== " << name << " ===\n";

    double measured = 0.0;
    double setpoint = 1.0;

    for (int i = 0; i < steps; ++i) {
        double control = controller.compute(setpoint, measured);
        measured = model(control);

        std::cout << "Step " << i
                  << " | Setpoint: " << setpoint
                  << " | Control: " << control
                  << " | Output: " << measured << "\n";
    }
    std::cout << name << " simulation finished.\n\n";
}

int main() {
    PID linearPID(1.0, 0.1, 0.05);
    PID nonlinearPID(1.0, 0.1, 0.05);

    int steps = 50;

    runSimulation(linearModel, steps, linearPID, "Linear Model");
    runSimulation(nonlinearModel, steps, nonlinearPID, "Nonlinear Model");

    std::cout << "Simulations completed.\n";
    return 0;
}
