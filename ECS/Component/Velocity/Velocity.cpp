/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Velocity
*/

#include "Velocity.hpp"

/**
 * @brief Constructs a new Velocity component with specified velocity.
 * @param velocityX The velocity of the entity on the X axis.
 * @param velocityY The velocity of the entity on the Y axis.
*/
Velocity::Velocity(float velocityX, float velocityY)
    : _velocityX(velocityX), _velocityY(velocityY)
{
}

/**
 * @brief Gets the velocity of an entity.
 *
 * @return A float to the actual velocity on the X axis of the entity.
 */
float Velocity::getVelocityX() const
{
    return _velocityX;
}

/**
 * @brief Updates the velocity of an entity.
 *
 * @param velocityX value used to change the velocity on the X axis of the entity.
 */
void Velocity::setVelocityX(float velocityX)
{
    _velocityX = velocityX;
}

/**
 * @brief Gets the velocity of an entity.
 *
 * @return A float to the actual velocity on the Y axis of the entity.
 */
float Velocity::getVelocityY() const
{
    return _velocityY;
}

/**
 * @brief Updates the velocity of an entity.
 *
 * @param velocityY value used to change the velocity on the Y axis of the entity.
 */
void Velocity::setVelocityY(float velocityY)
{
    _velocityY = velocityY;
}