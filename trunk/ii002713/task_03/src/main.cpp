#include "pid.h"
#include <iostream>

// Linear system with internal state
class LinearModel {
public:
    double operator()(double input) {
        constexpr double T = 0.05;
        state += T * input;  // accumulate dynamics
        return state;
    }

private:
    double state = 0.0;
};

// Nonlinear system with internal state
class NonlinearModel {
public:
    double operator()(double input) {
        constexpr double T = 0.05;
        state += T * input + 0.01 * input * input;  // nonlinear accumulation
        return state;
    }

private:
    double state = 0.0;
};

template <typename ModelFunc>
void runSimulation(ModelFunc model, int steps, PID& controller, const std::string& name){
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

    runSimulation(LinearModel{}, steps, linearPID, "Linear Model");
    runSimulation(NonlinearModel{}, steps, nonlinearPID, "Nonlinear Model");

    std::cout << "Simulations completed.\n";
    return 0;
}
