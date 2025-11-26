/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Scale
*/

#include "ScaleCollider.hpp"

/**
 * @brief Constructs a new Scale component with specified scale factors.
 * @param scale The scale factor for the collider. Default is 1.0f.
*/
ScaleCollider::ScaleCollider(float scale)
    : _scale(scale)
{
}

/**
 * @brief Gets the scale factor of the collider.
 * @return The scale factor of the collider.
*/
float ScaleCollider::getScale() const
{
    return _scale;
}


/**
 * @brief Sets the scale factor of the collider.
 * @param scaleX The new scale factor of the collider.
*/
void ScaleCollider::setScale(float scale)
{
    _scale = scale;
}
