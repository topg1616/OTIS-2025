#include <gtest/gtest.h>
#include "../src/pid.h"
#include "../src/model.h"

TEST(PIDTest, HoldsZeroWhenNoError) {
    PID pid(1.0, 1.0, 0.0, 1.0);
    double u = pid.compute(0.0, 0.0);
    EXPECT_NEAR(u, 0.0, 1e-6);
}

TEST(PIDTest, RespondsToStepChange) {
    PID pid(2.0, 5.0, 1.0, 1.0);
    double u1 = pid.compute(0.0, 1.0);
    double u2 = pid.compute(0.1, 1.0);
    EXPECT_GT(u1, 0.0);
    EXPECT_NE(u1, u2);
}

TEST(ModelTest, StepResponse) {
    Model m(0.9, 0.1);
    double y1 = m.step(1.0);
    double y2 = m.step(1.0);
    EXPECT_GT(y2, y1);
}
