#include "pid.h"
#include <gtest/gtest.h>
#include <cmath>
#include <limits>

/**
 * @brief Basic test: PID output approaches setpoint for constant error
 */
TEST(PIDTest, BasicResponse) {
    PID pid(1.0, 0.5, 0.1, 0.1);

    double setpoint = 1.0;
    double measured = 0.0;
    double u = pid.compute(setpoint, measured);

    // Should produce positive output when error is positive
    EXPECT_GT(u, 0.0);
}

/**
 * @brief Ensure inv_dt is correctly initialized even for invalid dt
 */
TEST(PIDTest, InvalidDtInitializesInvDt) {
    PID pid(1.0, 0.0, 1.0, -0.5); // invalid dt, will use DEFAULT_DT

    // Compute once to ensure no crash or undefined behavior
    double u = pid.compute(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(u)); // Output must be finite (no NaN or inf)
}

/**
 * @brief Test derivative scaling through inv_dt
 */
TEST(PIDTest, DerivativeScaling) {
    PID pid_fast(1.0, 0.0, 1.0, 0.1);
    PID pid_slow(1.0, 0.0, 1.0, 1.0);

    double setpoint = 1.0;

    // Simulate initial measurement
    double u_fast_before = pid_fast.compute(setpoint, 0.0);
    double u_slow_before = pid_slow.compute(setpoint, 0.0);
    // Now introduce small change in measurement
    double u_fast_after = pid_fast.compute(setpoint, 0.9);
    double u_slow_after = pid_slow.compute(setpoint, 0.9);
    // With smaller dt (larger inv_dt), derivative term dominates => bigger *change* in output
    double delta_u_fast = u_fast_after - u_fast_before;
    double delta_u_slow = u_slow_after - u_slow_before;
    EXPECT_GT(std::fabs(delta_u_fast), std::fabs(delta_u_slow));
}

/**
 * @brief Test that invalid output limits are ignored
 */
TEST(PIDTest, InvalidOutputLimitsIgnored) {
    PID pid(1.0, 0.0, 0.0, 0.1);
    pid.setOutputLimits(-1.0, 1.0);

    // Invalid call: should be ignored
    pid.setOutputLimits(2.0, -2.0);

    // After invalid call, old limits must remain valid
    double u = pid.compute(10.0, 0.0);
    EXPECT_LE(u, 1.0);
    EXPECT_GE(u, -1.0);
}

/**
 * @brief Test that integral limits are applied correctly
 */
TEST(PIDTest, IntegralLimitsWork) {
    PID pid(0.0, 1.0, 0.0, 0.1);
    pid.setIntegralLimits(-0.5, 0.5);

    // Force integral windup
    for (int i = 0; i < 100; ++i)
        pid.compute(10.0, 0.0);

    // Integral should be clamped
    double u = pid.compute(10.0, 0.0);
    EXPECT_LE(u, 0.5 + 1e-6);
    EXPECT_GE(u, -0.5 - 1e-6);
}
