#include <iostream>
#include <cmath>
using namespace std;

// линейная модель
double Linear(double a, double b, double u, double y) {
    return a * y + b * u;
}

// симуляция линейной модели
void simulateLinear(double a, double b, double u, int steps) {
    cout << "Линейная модель" << endl;
    double y = 0.0;
    for (int i = 0; i < steps; ++i) {
        cout << "Шаг " << i << ": " << y << endl;
        y = Linear(a, b, u, y);
    }
    cout << endl;
}

// нелинейная модель
double Nonlinear(double a, double b, double c, double d, double u, double uPrev, double y, double yPrev) {
    return a * y - b * (yPrev * yPrev) + c * u + d * sin(uPrev);
}

// симуляция нелинейной модели
void simulateNonlinear(double a, double b, double c, double d, double u, int steps) {
    cout << "Нелинейная модель" << endl;
    double y = 0.0;
    double yPrev = 0.0;
    double uPrev = 0.0;
    for (int i = 0; i < steps; ++i) {
        cout << "Шаг " << i << ": " << y << endl;
        double yNext = Nonlinear(a, b, c, d, u, uPrev, y, yPrev);
        yPrev = y;
        uPrev = u;
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