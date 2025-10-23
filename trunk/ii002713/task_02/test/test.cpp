#include <gtest/gtest.h>
#include <cmath>
#include "model.h"

// тесты для линейной модели
TEST(LinearModelTest, BaseCase) {
    EXPECT_NEAR(Linear(0.1, 0.3, 0.5, 0.0), 0.15, 1e-6);
}

TEST(LinearModelTest, WithNonZeroY) {
    EXPECT_NEAR(Linear(0.2, 0.4, 1.0, 2.0), 0.8, 1e-6);
}

// тесты для нелинейной модели
TEST(NonlinearModelTest, BaseCase) {
    NonlinearParams p{0.7, 0.9, 0.11, 0.13};
    double result = Nonlinear(p, 0.15, 0.0, 0.0, 0.0);
    double expected = p.c * 0.15 + p.d * sin(0.0);
    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, WithPreviousValues) {
    NonlinearParams p{0.5, 0.2, 0.3, 0.1};
    double result = Nonlinear(p, 0.4, 0.3, 0.5, 0.2);
    double expected = 0.5 * 0.5 - 0.2 * (0.2 * 0.2) + 0.3 * 0.4 + 0.1 * sin(0.3);
    EXPECT_NEAR(result, expected, 1e-6);
}