#include <iostream>
#include <cmath>
using namespace std;

// значение линейной модели
double Linear(double a, double b, double u, double y) {
    return a * y + b * u;
}

// симуляция линейной модели
void simulateLinear(double a, double b, double u, int steps) {
    cout << "Линейная модель" << endl;
    double y = 0.0;
    for (int i = 0; i < steps; ++i) {
        cout << "Step " << i << ": " << y << endl;
        y = Linear(a, b, u, y);
    }
    cout << endl;
}

// значение нелинейной модели
double Nonlinear(double a, double b, double c, double d, double u, double y, double yPrev, bool firstStep) {
    if (firstStep) {
        // первый шаг - фикс значение вместо u и yPrev
        return a * y - b * (yPrev * yPrev) + c * 1.0 + d * sin(1.0);
    }
    return a * y - b * (yPrev * yPrev) + c * u + d * sin(u);
}

// симуляция нелинейной модели
void simulateNonlinear(double a, double b, double c, double d, double u, int steps) {
    cout << "Нелинейная модель" << endl;
    double y = 0.0;
    double yPrev = 0.0;
    bool firstStep = true;
    for (int i = 0; i < steps; ++i) {
        cout << "Step " << i << ": " << y << endl;
        double yNext = Nonlinear(a, b, c, d, u, y, yPrev, firstStep);
        firstStep = false;
        yPrev = y;
        y = yNext;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");

    // параметры линейной модели
    double a1 = 0.1;
    double b1 = 0.3;
    double u1 = 0.5;
    int n1 = 10;

    simulateLinear(a1, b1, u1, n1);

    // параметры нелинейной модели
    double a2 = 0.7;
    double b2 = 0.9;
    double c2 = 0.11;
    double d2 = 0.13;
    double u2 = 0.15;
    int n2 = 10;

    simulateNonlinear(a2, b2, c2, d2, u2, n2);

    return 0;
}