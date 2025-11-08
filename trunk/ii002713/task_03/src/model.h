#ifndef MODEL_H
#define MODEL_H

/**
 * @brief Simple dynamic model for simulation purposes.
 *
 * The Model class represents a system whose state is described by the variable @c y.
 * The state @c y can be initialized and updated via the provided methods.
 */
class Model {
private:
    /**
     * @brief Current state of the model.
     *
     * Represents the output or state variable of the model.
     */
    double y{0.0};  // in-class инициализация

public:
    /**
     * @brief Construct the model with an initial state.
     * @param y0 Initial state value (default 0.0)
     */
    explicit Model(double y0 = 0.0) noexcept;

    /**
     * @brief Get current state.
     * @return Current value of y
     */
    double getY() const noexcept;

    /**
     * @brief Update the state by adding input u (y += u).
     * @param u Input
     */
    void update(double u) noexcept;
};

#endif // MODEL_H
