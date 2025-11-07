#include <iostream>
#include "pid.h"
#include "model.h"

using namespace std;

/**
 * @brief Тестовая программа моделирования системы «объект + ПИД-регулятор».
 */
int main() {
    PID pid(2.0, 5.0, 1.0, 1.0);
    Model model(0.9, 0.1);

    double yzad = 1.0;
    cout << "k\ty(k)\tu(k)\n";

    for (int k = 0; k < 20; ++k) {
        double y = model.getY();
        double u = pid.compute(y, yzad);
        double y_next = model.step(u);
        cout << k << "\t" << y_next << "\t" << u << "\n";
    }

    return 0;
}
