/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Rotation
*/

#include "Rotation.hpp"

/**
 * @brief Gets the Rotation factor of the collider.
 * @return The Rotation factor of the collider.
*/
float Rotation::getRotation() const
{
    return _rotation;
}


/**
 * @brief Sets the Rotation factor of the collider.
 * @param rotation The new Rotation factor of the collider.
*/
void Rotation::setRotation(float rotation)
{
    _rotation = rotation;
}
