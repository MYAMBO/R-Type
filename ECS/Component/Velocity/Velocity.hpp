/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Velocity
*/


#ifndef R_TYPE_VELOCITY_HPP
    #define R_TYPE_VELOCITY_HPP

#include "Component.hpp"

/**
 * @brief Velocity component to define the movement speed of an entity.
 *
 * This component holds the velocity value of an entity.
 * It provides methods to retrieve and modify the velocity.
*/
class Velocity : public Component {
    public:
        explicit Velocity(float velocity);
        ~Velocity() override = default;

    [[nodiscard]] float getVelocity() const;

    void setVelocity(float velocity);

    private:
        float _velocity;

};

#endif //R_TYPE_VELOCITY_HPP
