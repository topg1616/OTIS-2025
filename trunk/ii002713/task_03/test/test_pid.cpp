#include <gtest/gtest.h>
#include "pid.h"
#include "model.h"

TEST(ModelTest, UpdateIncreasesWithPositiveInput) {
    Model model;
    model.update(1.0);
    EXPECT_GT(model.getY(), 0.0);
}

TEST(PIDTest, ComputeRespondsToError) {
    PID pid(2.0, 1.0, 0.1, 0.1);
    double u1 = pid.compute(1.0, 0.0);
    double u2 = pid.compute(2.0, 0.0);
    EXPECT_GT(u2, u1);
}

TEST(PIDTest, ComputeStabilizesAtZeroError) {
    PID pid(1.0, 1.0, 0.05, 0.1);
    pid.compute(1.0, 0.0);
    double u = pid.compute(0.0, 0.0);
    // Ожидаем, что сигнал будет близок к нулю — допустимая дельта 1.0
    EXPECT_NEAR(u, 0.0, 1.0);
}

TEST(SystemTest, PIDControlsModel) {
    PID pid(2.0, 1.0, 0.05, 0.1);
    pid.setOutputLimits(-10.0, 10.0);
    pid.setIntegralLimits(-5.0, 5.0);

    Model model;
    const double setpoint = 1.0;

    for (int i = 0; i < 200; ++i) {
        double u = pid.compute(setpoint, model.getY());
        model.update(u);
    }

    EXPECT_NEAR(model.getY(), 1.0, 0.2);
}
