#include "model.h"

// Constructor
Model::Model(double y0) noexcept : y(y0) {}

// Get current state
double Model::getY() const noexcept {
    return y;
}

// Update state
void Model::update(double u) noexcept {
    y += u;
}
