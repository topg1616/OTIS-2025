#include <gtest/gtest.h>
#include "model.h"
#include "pid.h"

// Тесты класса Model
TEST(ModelTest, InitialValueIsSetCorrectly) {
    Model model(5.0);
    EXPECT_DOUBLE_EQ(model.getY(), 5.0);
}

TEST(ModelTest, UpdateChangesOutputTowardsControl) {
    Model model(0.0);
    model.update(10.0);
    EXPECT_GT(model.getY(), 0.0);
    EXPECT_LT(model.getY(), 10.0);
}

TEST(ModelTest, UpdateStabilizesOnConstantInput) {
    Model model(0.0);
    for (int i = 0; i < 100; ++i) {
        model.update(10.0);
    }
    EXPECT_NEAR(model.getY(), 10.0, 1e-3);
}

// Тесты класса PID
TEST(PIDTest, ConstructorInitializesValues) {
    PID pid(2.0, 5.0);
    EXPECT_NEAR(pid.getU(), 0.0, 1e-9);
}

TEST(PIDTest, ComputeIncreasesOutputForPositiveError) {
    PID pid(1.0, 1.0);
    double u1 = pid.compute(1.0);
    EXPECT_GT(u1, 0.0);
}

TEST(PIDTest, ComputeDecreasesOutputForNegativeError) {
    PID pid(1.0, 1.0);
    pid.compute(1.0);
    double u2 = pid.compute(-1.0);
    EXPECT_LT(u2, 0.0);
}

TEST(PIDTest, ComputeStabilizesAroundZeroError) {
    PID pid(1.0, 1.0);
    double prevU = 0.0;
    for (int i = 0; i < 20; ++i) {
        double u = pid.compute(0.0);
        EXPECT_NEAR(u, prevU, 0.5);
        prevU = u;
    }
}

// Интеграционный тест PID + Model
TEST(SystemIntegrationTest, PIDControlsModelToTarget) {
    const double setpoint = 10.0;
    PID pid(0.5, 0.1);
    Model model(0.0);

    double y = model.getY();

    for (int i = 0; i < 200; ++i) {
        double error = setpoint - y;
        double control = pid.compute(error);
        model.update(control);
        y = model.getY();
    }

    // Проверяем, что система стабилизировалась около setpoint
    EXPECT_NEAR(y, setpoint, 0.5);
}
