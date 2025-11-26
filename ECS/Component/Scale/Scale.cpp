/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Scale
*/

#include "Scale.hpp"

/**
 * @brief Constructs a new Scale component with specified scale factors.
 * @param scaleX The scale factor in the X direction. Default is 1.0f.
 * @param scaleY The scale factor in the Y direction. Default is 1.0f.
*/
Scale::Scale(float scaleX, float scaleY)
    : _scaleX(scaleX), _scaleY(scaleY)
{
}

/**
 * @brief Gets the scale factor in the X direction.
 * @return The scale factor in the X direction.
*/
float Scale::getScaleX() const
{
    return _scaleX;
}

/**
 * @brief Gets the scale factor in the Y direction.
 * @return The scale factor in the Y direction.
*/
float Scale::getScaleY() const
{
    return _scaleY;
}

/**
 * @brief Sets the scale factor in the X direction.
 * @param scaleX The new scale factor in the X direction.
*/
void Scale::setScaleX(float scaleX)
{
    _scaleX = scaleX;
}

/**
 * @brief Sets the scale factor in the Y direction.
 * @param scaleY The new scale factor in the Y direction.
*/
void Scale::setScaleY(float scaleY)
{
    _scaleY = scaleY;
}