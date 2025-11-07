#include "model.h"

// Конструктор теперь использует только аргумент
Model::Model(double y0) noexcept : y(y0) {}

double Model::getY() const noexcept {
    return y;
}

void Model::update(double u) noexcept {
    y += u;
}
