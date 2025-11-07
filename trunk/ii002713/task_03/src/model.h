#ifndef MODEL_H
#define MODEL_H

/**
 * @brief Simple dynamic model for simulation purposes.
 *
 * The Model class represents a system whose state is described by the variable @c y.
 * You can initialize state and update it using update(u) (here model is y += u).
 */
class Model {
private:
    /**
     * @brief Current state of the model.
     */
    double y{0.0};

public:
    /**
     * @brief Construct a Model with optional initial value.
     * @param y0 initial state (default 0.0)
     */
    explicit Model(double y0 = 0.0) noexcept;

    /**
     * @brief Get current state.
     * @return current y
     */
    double getY() const noexcept;

    /**
     * @brief Update state with input u (simple integrator: y += u).
     * @param u input value
     */
    void update(double u) noexcept;
};

#endif // MODEL_H
