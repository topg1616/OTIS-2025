#include "model.h"

Model::Model() : y(0.0) {}

double Model::update(double u, double dt) {
    // Простая линейная модель первого порядка: dy/dt = -y + u
    y += dt * (-y + u);
    return y;
}

double Model::getOutput() const {
    return y;
}
