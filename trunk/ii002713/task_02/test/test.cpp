#include <gtest/gtest.h>
#include <cmath>
#include "model.h"

// Тесты для линейной модели
TEST(LinearModelTest, BaseCase) {
    // Проверка базового случая:
    // a=0.1, b=0.3, y=0.5, u=0.0
    // Linear(a,b,y,u) = a*y + b*u = 0.1*0.5 + 0.3*0.0 = 0.05
    EXPECT_NEAR(Linear(0.1, 0.3, 0.5, 0.0), 0.05, 1e-6);
}

TEST(LinearModelTest, WithNonZeroY) {
    // Проверка случая с ненулевым y и u:
    // a=0.2, b=0.4, y=1.0, u=2.0
    // Linear(a,b,y,u) = 0.2*1.0 + 0.4*2.0 = 1.0
    EXPECT_NEAR(Linear(0.2, 0.4, 1.0, 2.0), 1.0, 1e-6);
}

// Тесты для нелинейной модели
TEST(NonlinearModelTest, BaseCase) {
    NonlinearParams p{0.7, 0.9, 0.11, 0.13};
    // Проверка базового случая:
    // Nonlinear(p, y, y_prev, u_prev, u_prev2)
    double result = Nonlinear(p, 0.15, 0.0, 0.0, 0.0);
    double expected = p.c * 0.15 + p.d * sin(0.0);
    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, WithPreviousValues) {
    NonlinearParams p{0.5, 0.2, 0.3, 0.1};
    // Проверка случая с предыдущими значениями:
    // Nonlinear(p, y, y_prev, u_prev, u_prev2)
    double result = Nonlinear(p, 0.4, 0.3, 0.5, 0.2);
    double expected = 0.5 * 0.5 - 0.2 * (0.2 * 0.2) + 0.3 * 0.4 + 0.1 * sin(0.3);
    EXPECT_NEAR(result, expected, 1e-6);
}
