#include <gtest/gtest.h>
#include <cmath>
#include "model.h"

// Тесты для линейной модели
TEST(LinearModelTest, BaseCase) {
    // a=0.1, b=0.3, u=0.5, y=0.0
    // Linear(a,b,u,y) = a*y + b*u = 0.1*0.0 + 0.3*0.5 = 0.15
    EXPECT_NEAR(Linear(0.1, 0.3, 0.5, 0.0), 0.15, 1e-6);
}

TEST(LinearModelTest, WithNonZeroY) {
    // a=0.2, b=0.4, u=2.0, y=1.0
    // Linear(a,b,u,y) = 0.2*1.0 + 0.4*2.0 = 1.0
    EXPECT_NEAR(Linear(0.2, 0.4, 2.0, 1.0), 1.0, 1e-6);
}

// Тесты для нелинейной модели
TEST(NonlinearModelTest, BaseCase) {
    NonlinearParams p{0.7, 0.9, 0.11, 0.13};
    // Nonlinear(p, u, uPrev, y, yPrev)
    // u=0.15, uPrev=0.0, y=0.0, yPrev=0.0
    double result = Nonlinear(p, 0.15, 0.0, 0.0, 0.0);
    double expected = p.c * 0.15 + p.d * std::sin(0.0);
    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, WithPreviousValues) {
    NonlinearParams p{0.5, 0.2, 0.3, 0.1};
    // Nonlinear(p, u, uPrev, y, yPrev)
    // u=0.4, uPrev=0.3, y=0.5, yPrev=0.2
    double result = Nonlinear(p, 0.4, 0.3, 0.5, 0.2);
    double expected = 0.5 * 0.5 - 0.2 * (0.2 * 0.2) + 0.3 * 0.4 + 0.1 * std::sin(0.3);
    EXPECT_NEAR(result, expected, 1e-6);
}
