#ifndef PID_H
#define PID_H

class PID {
private:
    double Kp{0.0};
    double Ki{0.0};
    double Kd{0.0};
    double dt{0.1};

    double prev_error{0.0};
    double integral{0.0};

    double output_min{-1e9};
    double output_max{1e9};
    double integral_min{-1e6};
    double integral_max{1e6};

public:
    explicit PID(double Kp_ = 0.0, double Ki_ = 0.0, double Kd_ = 0.0, double dt_ = 0.1) noexcept;

    double compute(double setpoint, double measured) noexcept;
    void reset() noexcept;

    void setOutputLimits(double min, double max) noexcept;
    void setIntegralLimits(double min, double max) noexcept;
};

#endif // PID_H
