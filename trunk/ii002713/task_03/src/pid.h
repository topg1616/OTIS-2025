#ifndef PID_H
#define PID_H

class PID {
public:
    // Конструктор
    PID(double Kp_, double Ki_, double Kd_, double dt_) noexcept;

    // Вычисление PID-сигнала
    double compute(double setpoint, double measured) noexcept;

    // Сброс состояния PID
    void reset() noexcept;

    // Ограничения выхода и интеграла
    void setOutputLimits(double min, double max) noexcept;
    void setIntegralLimits(double min, double max) noexcept;

    // Изменение времени дискретизации
    void setDt(double new_dt) noexcept;

private:
    double Kp;
    double Ki;
    double Kd;

    double dt;
    double inv_dt;

    double prev_error = 0.0;       // in-class initializer
    double integral   = 0.0;       // in-class initializer

    double output_min   = -1e9;    // in-class initializer
    double output_max   =  1e9;    // in-class initializer
    double integral_min = -1e9;    // in-class initializer
    double integral_max =  1e9;    // in-class initializer

    static constexpr double DEFAULT_DT = 0.01; // default timestep
};

#endif // PID_H
