#include <gtest/gtest.h>
#include "pid.h"
#include "model.h"

// Тесты PID-регулятора

TEST(PIDTest, OutputIncreasesWithError) {
    PID pid(2.0, 0.0, 0.0, 0.1); // Только пропорциональный коэффициент
    double u1 = pid.compute(1.0, 0.0);
    double u2 = pid.compute(2.0, 0.0);
    EXPECT_GT(u2, u1);
}

TEST(PIDTest, StabilizesNearZeroError) {
    PID pid(1.0, 0.5, 0.1, 0.1);
    pid.compute(1.0, 0.0);  // первый шаг
    pid.compute(1.0, 1.0);  // ошибка = 0
    double u = pid.compute(1.0, 1.0);
    EXPECT_NEAR(u, 0.0, 5.0);
}

TEST(PIDTest, ResetClearsInternalState) {
    PID pid(1.0, 1.0, 0.0, 0.1);
    pid.compute(2.0, 0.0);
    pid.reset();
    double u = pid.compute(2.0, 0.0);
    EXPECT_NEAR(u, 2.0, 1.0); // после сброса нет накопленной ошибки
}

// Тесты модели

TEST(ModelTest, UpdateRespondsToInput) {
    Model m;
    double initial = m.getY();
    m.update(1.0);
    EXPECT_GT(m.getY(), initial);
}

TEST(ModelTest, OutputChangesGradually) {
    Model m;
    double prev = m.getY();
    for (int i = 0; i < 10; ++i) {
        m.update(0.5);
    }
    EXPECT_GT(m.getY(), prev);
}

// Совместная работа PID и модели

TEST(SystemTest, PIDControlsModelToSetpoint) {
    PID pid(2.0, 1.0, 0.1, 0.1);
    Model model;
    const double setpoint = 1.0;

    for (int i = 0; i < 100; ++i) {
        double u = pid.compute(setpoint, model.getY());
        model.update(u);
    }

    EXPECT_NEAR(model.getY(), setpoint, 0.3);
}
