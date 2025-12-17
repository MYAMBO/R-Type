/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Rotation
*/

#include <cmath>

#include "Rotation.hpp"

/**
 * @brief Constructs a new Rotation component with specified rotation factors.
 * @param rotation The rotation factor for the component. Default is 0.0f.
 * @tparam T The type of the component, used to set the type string.
*/
Rotation::Rotation(float rotation)
{
    rotation = std::fmod(rotation, 360.0f);
    _rotation = rotation;
}

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
void Rotation::setRotation(const float rotation)
{
    _rotation = rotation;
}
