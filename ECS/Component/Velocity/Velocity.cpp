/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Velocity
*/

#include "Velocity.hpp"

/**
 * @brief Constructs a new Velocity component with specified velocity.
 * @param velocity The velocity value.
*/
Velocity::Velocity(const float velocity) : _velocity(velocity)
{
}

/**
 * @brief Gets the velocity of an entity.
 *
 * @return A float to the actual velocity of the entity.
 */
float Velocity::getVelocity() const
{
    return _velocity;
}

/**
 * @brief Updates the velocity of an entity.
 *
 * @param velocity value used to change the velocity of the entity.
 */
void Velocity::setVelocity(const float velocity)
{
    _velocity = velocity;
}
