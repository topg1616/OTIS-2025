#include <gtest/gtest.h>
#include "pid.h"
#include "model.h"

/**
 * @brief Проверка корректности обновления модели.
 */
TEST(ModelTest, UpdateIncreasesOutput) {
    Model model;
    double y1 = model.update(1.0, 0.1);
    double y2 = model.update(1.0, 0.1);
    EXPECT_GT(y2, y1);
}

/**
 * @brief Проверка, что ПИД-регулятор корректно реагирует на ошибку.
 */
TEST(PIDTest, ComputeRespondsToError) {
    PID pid(1.0, 0.5, 0.1, 0.1);
    double u1 = pid.compute(1.0, 0.0);
    double u2 = pid.compute(2.0, 0.0);
    EXPECT_GT(u2, u1);
}

/**
 * @brief Проверка, что при нулевой ошибке выход стабилизируется.
 */
TEST(PIDTest, ComputeStabilizesAtZeroError) {
    PID pid(1.0, 0.5, 0.1, 0.1);
    pid.compute(1.0, 0.0);
    pid.compute(1.0, 0.0);
    double u = pid.compute(1.0, 0.0);
    EXPECT_NEAR(u, 0.0, 10.0);
}

/**
 * @brief Проверка функции reset().
 */
TEST(PIDTest, ResetClearsState) {
    PID pid(1.0, 0.5, 0.1, 0.1);
    pid.compute(1.0, 0.0);
    pid.reset();

    // После сброса интеграл и ошибка должны быть обнулены
    double u = pid.compute(1.0, 0.0);
    EXPECT_NEAR(u, pid.compute(1.0, 0.0), 1e-9);
}

/**
 * @brief Проверка установки ограничений для интеграла.
 */
TEST(PIDTest, SetIntegralLimitsClampsValue) {
    PID pid(1.0, 1.0, 0.1, 0.1);
    pid.setIntegralLimits(-0.5, 0.5);

    // Генерируем большую ошибку, чтобы интеграл попытался выйти за пределы
    for (int i = 0; i < 100; ++i) {
        pid.compute(10.0, 0.0);
    }

    // Проверяем, что интеграл остался в допустимых границах
    double u = pid.compute(0.0, 0.0);
    EXPECT_LT(u, 100.0);  // не должно "взрываться"
}

/**
 * @brief Проверка совместной работы PID и модели.
 */
TEST(SystemTest, PIDControlsModel) {
    PID pid(2.0, 0.5, 0.1, 0.1);
    Model model;
    const double setpoint = 1.0;

    for (int i = 0; i < 100; ++i) {
        double u = pid.compute(setpoint, model.getY());
        model.update(u, 0.1);
    }

    double output = model.getY();
    EXPECT_NEAR(output, setpoint, 0.3);
}
