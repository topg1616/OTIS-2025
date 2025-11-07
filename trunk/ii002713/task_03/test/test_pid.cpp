#include <gtest/gtest.h>
#include "pid.h"
#include "model.h"

/**
 * @brief Тест проверяет корректность работы метода Model.
 */
TEST(ModelTest, UpdateIncreasesWithPositiveInput) {
    Model model;
    double y1 = model.update(1.0, 0.1);
    double y2 = model.update(1.0, 0.1);
    EXPECT_GT(y2, y1);
}

/**
 * @brief Тест проверяет, что ПИД-регулятор корректно реагирует на ошибку.
 */
TEST(PIDTest, ComputeRespondsToError) {
    PID pid(2.0, 1.0, 0.1);
    double u1 = pid.compute(1.0);
    double u2 = pid.compute(2.0);
    EXPECT_GT(u2, u1);
}

/**
 * @brief Тест проверяет, что при нулевой ошибке выход не растёт бесконечно.
 */
TEST(PIDTest, ComputeStabilizesAtZeroError) {
    PID pid(1.0, 1.0, 0.1);
    pid.compute(1.0);
    pid.compute(0.0);
    double u = pid.compute(0.0);
    EXPECT_NEAR(u, 0.0, 10.0);  // Проверка, что сигнал не выходит за разумные пределы
}

/**
 * @brief Тест проверяет совместную работу ПИД-регулятора и модели.
 */
TEST(SystemTest, PIDControlsModel) {
    PID pid(2.0, 1.0, 0.1);
    Model model;
    const double setpoint = 1.0;

    for (int i = 0; i < 100; ++i) {
        double error = setpoint - model.getOutput();
        double u = pid.compute(error);
        model.update(u, 0.1);
    }

    double output = model.getOutput();
    EXPECT_NEAR(output, 1.0, 0.2);
}
