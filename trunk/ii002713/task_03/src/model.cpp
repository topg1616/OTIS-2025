#include "model.h"

Model::Model(double y0) {
    y = y0;
}

double Model::getY() const {
    return y;
}

void Model::update(double u) {
    // Простая инерционная модель первого порядка
    const double a = 0.1;
    y += a * (u - y);
}
