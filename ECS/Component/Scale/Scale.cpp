/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Scale
*/

#include "Scale.hpp"

Scale::Scale(float scale)
        : _scale(scale), _type("Scale")
{
}

/**
 * @brief Gets the scale factor of the sprite.
 * @return The scale factor of the sprite.
*/
float Scale::getScale() const
{
    return _scale;
}


/**
 * @brief Sets the scale factor of the sprite.
 * @param scaleX The new scale factor of the sprite.
*/
void Scale::setScale(float scale)
{
    _scale = scale;
}
