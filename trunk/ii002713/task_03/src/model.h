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
    double y{0.0};  // in-class initialization

public:
    /**
     * @brief Construct a Model with optional initial value
     * @param y0 Initial value of the state
     */
    explicit Model(double y0 = 0.0) noexcept;

    /// Get current state
    double getY() const noexcept;

    /// Update state by control input u
    void update(double u) noexcept;
};

#endif // MODEL_H
