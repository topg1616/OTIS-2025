#include "pid.h"
#include <iostream>
#include <string>

/**
 * @brief Шаблонная модель динамической системы.
 * Хранит внутреннее состояние, обновляет его через правило UpdateRule.
 */
template <typename UpdateRule>
class SystemModel {
public:
    double operator()(double input) {
        state = updateRule(state, input);
        return state;
    }

private:
    double state = 0.0;
    UpdateRule updateRule;
};

/**
 * @brief Линейная система: y(t+1) = y(t) + T * u
 * Простая тепловая модель без нелинейностей.
 */
struct LinearUpdate {
    double operator()(double state, double input) const {
        constexpr double T = 0.05;
        return state + T * input;
    }
};

/**
 * @brief Нелинейная система: y(t+1) = y(t) + T*u + α*u²
 * Ускоряет рост при сильном нагреве.
 */
struct NonlinearUpdate {
    double operator()(double state, double input) const {
        constexpr double T = 0.05;
        return state + T * input + 0.01 * input * input;
    }
};

using LinearModel    = SystemModel<LinearUpdate>;
using NonlinearModel = SystemModel<NonlinearUpdate>;

template <typename Model>
void runSimulation(Model model, int steps, PID& controller, const std::string& name)
{
    std::cout << "=== " << name << " ===\n";

    double measured = 0.0;
    const double setpoint = 1.0;

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

    const int steps = 50;

    runSimulation(LinearModel{}, steps, linearPID, "Linear Model");
    runSimulation(NonlinearModel{}, steps, nonlinearPID, "Nonlinear Model");

    std::cout << "Simulations completed.\n";
    return 0;
}
