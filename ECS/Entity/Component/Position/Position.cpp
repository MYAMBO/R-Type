/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Position
*/

#include "Position.hpp"

/**
 * @brief Constructs a new Position component with specified coordinates.
*/
Position::Position(float x, float y) : _x(x), _y(y) {}

/**
 * @brief Gets the X coordinate.
*/
float Position::getX() const { return _x; }

/**
 * @brief Gets the Y coordinate.
*/
float Position::getY() const { return _y; }

/**
 * @brief Sets the X coordinate.
*/
void Position::setX(float x) { _x = x; }

/**
 * @brief Sets the Y coordinate.
*/
void Position::setY(float y) { _y = y; }
