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
     * @brief Construct a new Model object
     * @param y0 Initial state value (default 0.0)
     */
    explicit Model(double y0 = 0.0) noexcept;

    /**
     * @brief Get the current state
     * @return Current value of y
     */
    double getY() const noexcept;

    /**
     * @brief Update the state with input u
     * @param u Input to update the model
     */
    void update(double u) noexcept;
};

#endif // MODEL_H
