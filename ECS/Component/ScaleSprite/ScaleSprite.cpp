/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Scale
*/

#include "ScaleSprite.hpp"

/**
 * @brief Constructs a new Scale component with specified scale factors.
 * @param scale The scale factor for the sprite. Default is 1.0f.
*/
ScaleSprite::ScaleSprite(float scale)
    : _scale(scale)
{
}

/**
 * @brief Gets the scale factor of the sprite.
 * @return The scale factor of the sprite.
*/
float ScaleSprite::getScale() const
{
    return _scale;
}


/**
 * @brief Sets the scale factor of the sprite.
 * @param scaleX The new scale factor of the sprite.
*/
void ScaleSprite::setScale(float scale)
{
    _scale = scale;
}
