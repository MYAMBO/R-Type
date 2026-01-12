/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Position
*/

#include "Position.hpp"

/**
 * @brief Constructs a new Position component with specified coordinates.
 * @param x The X coordinate.
 * @param y The Y coordinate.
*/
Position::Position(float x, float y)
    : _x(x), _y(y)
{
}

/**
 * @brief Gets the X coordinate.
 * @return The X coordinate.
*/
float Position::getX() const
{
    return _x;
}
/**
 * @brief Gets the Y coordinate.
 * @return The Y coordinate.
*/
float Position::getY() const
{
    return _y;
}
/**
 * @brief Sets the X coordinate.
 * @param x The new X coordinate.
*/
void Position::setX(const float x)
{
    _x = x;
}
/**
 * @brief Sets the Y coordinate.
 * @param y The new Y coordinate.
*/
void Position::setY(const float y)
{
    _y = y;
}
/**
 * @brief Gets the target X coordinate.
 * @return The target X coordinate.
*/
float Position::getTargetX() const
{
    return _targetX;
}

/**
 * @brief Gets the target Y coordinate.
 * @return The target Y coordinate.
*/
float Position::getTargetY() const
{
    return _targetY;
}

/**
 * @brief Sets the target X coordinate.
 * @param x The new target X coordinate.
*/
void Position::setTargetX(const float x)
{
    _targetX = x;
}

/**
 * @brief Sets the target Y coordinate.
 * @param y The new target Y coordinate.
*/
void Position::setTargetY(const float y)
{
    _targetY = y;
}