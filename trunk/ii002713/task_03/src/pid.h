#ifndef PID_H
#define PID_H

class PID {
private:
    double Kp;
    double Ki;
    double Kd;
    double dt;
    double prev_error;
    double integral;
    double output_min;
    double output_max;
    double integral_min;
    double integral_max;

public:
    explicit PID(double Kp_ = 0.0, double Ki_ = 0.0, double Kd_ = 0.0, double dt_ = 0.1) noexcept;

    double compute(double setpoint, double measured) noexcept;
    void reset() noexcept;

    // Опционально: ограничения выхода/интеграла
    void setOutputLimits(double min, double max) noexcept;
    void setIntegralLimits(double min, double max) noexcept;
};

#endif // PID_H
