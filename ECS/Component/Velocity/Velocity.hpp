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
        explicit Velocity(float velocityX, float velocityY);
        ~Velocity() override = default;

    [[nodiscard]] float getVelocityX() const;
    [[nodiscard]] float getVelocityY() const;

    void setVelocityX(float velocityX);
    void setVelocityY(float velocityY);

    private:
        float _velocityX;
        float _velocityY;

};

#endif //R_TYPE_VELOCITY_HPP
