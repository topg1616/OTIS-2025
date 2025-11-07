#include "model.h"

Model::Model(double y0) noexcept
    : y(y0) {}

// Получение текущего состояния
double Model::getY() const noexcept {
    return y;
}

// Обновление состояния (интегратор)
void Model::update(double u) noexcept {
    y += u;
}
