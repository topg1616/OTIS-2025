#ifndef MODEL_H
#define MODEL_H

/**
 * @brief Simple dynamic model used for simulation.
 *
 * The Model class represents a system with a single state variable y.
 * The model used here is a simple integrator: y <- y + u.
 */
class Model {
private:
    /**
     * @brief Current state of the model.
     */
    double y{0.0};

public:
    /**
     * @brief Construct the model with an initial state.
     * @param y0 initial state value (default 0.0)
     */
    explicit Model(double y0 = 0.0) noexcept;

    /**
     * @brief Get current state.
     * @return current value of y
     */
    double getY() const noexcept;

    /**
     * @brief Update the state by adding input u (y += u).
     * @param u input
     */
    void update(double u) noexcept;
};

#endif // MODEL_H
