#include "model.h"

Model::Model(double y0) noexcept
    : y(y0) {}

double Model::getY() const noexcept {
    return y;
}

double Model::update(double u, double dt) noexcept {
    // простая динамическая модель интегратора: y += u * dt
    y += u * dt;
    return y;
}
