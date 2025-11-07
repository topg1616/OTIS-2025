#include "model.h"

Model::Model(double a1_, double b1_) : a1(a1_), b1(b1_), y(0.0) {}

double Model::step(double u) {
    y = a1 * y + b1 * u;
    return y;
}

double Model::getY() const {
    return y;
}

void Model::reset(double value) {
    y = value;
}
