#ifndef MODEL_H
#define MODEL_H

class Model {
private:
    double y{0.0};  // in-class инициализация

public:
    explicit Model(double y0 = 0.0) noexcept;

    double getY() const noexcept;
    void update(double u) noexcept;
};

#endif // MODEL_H
