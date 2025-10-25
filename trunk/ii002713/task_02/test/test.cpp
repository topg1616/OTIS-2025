#include <gtest/gtest.h>
#include <cmath>
#include "model.h"

// Тесты для линейной модели

// Базовый случай: y=0, u=0.5, a=0.1, b=0.3
// Linear(a,b,u,y) = a*y + b*u = 0.1*0.0 + 0.3*0.5 = 0.15
TEST(LinearModelTest, BaseCase) {
    EXPECT_NEAR(Linear(0.1, 0.3, 0.5, 0.0), 0.15, 1e-6);
}

// Проверка с ненулевым y: y=1.0, u=2.0, a=0.2, b=0.4
// Linear(a,b,u,y) = 0.2*1.0 + 0.4*2.0 = 1.0
TEST(LinearModelTest, WithNonZeroY) {
    EXPECT_NEAR(Linear(0.2, 0.4, 2.0, 1.0), 1.0, 1e-6);
}

// Тесты для нелинейной модели

// Базовый случай: y=0, yPrev=0, u=0.15, uPrev=0
// Nonlinear(p,u,uPrev,y,yPrev) = p.c*u + p.d*sin(uPrev) = 0.11*0.15 + 0.13*sin(0) = 0.0165
TEST(NonlinearModelTest, BaseCase) {
    NonlinearParams p{0.7, 0.9, 0.11, 0.13};
    double result = Nonlinear(p, 0.15, 0.0, 0.0, 0.0);
    double expected = p.c * 0.15 + p.d * std::sin(0.0);
    EXPECT_NEAR(result, expected, 1e-6);
}

// С учетом предыдущих значений: y=0.5, yPrev=0.2, u=0.4, uPrev=0.3
// Nonlinear(p,u,uPrev,y,yPrev) = p.a*y - p.b*yPrev^2 + p.c*u + p.d*sin(uPrev)
TEST(NonlinearModelTest, WithPreviousValues) {
    NonlinearParams p{0.5, 0.2, 0.3, 0.1};
    double result = Nonlinear(p, 0.4, 0.3, 0.5, 0.2);
    double expected = 0.5 * 0.5 - 0.2 * (0.2 * 0.2) + 0.3 * 0.4 + 0.1 * std::sin(0.3);
    EXPECT_NEAR(result, expected, 1e-6);
}
