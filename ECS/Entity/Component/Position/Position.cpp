/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Position
*/

#include "Position.hpp"

Position::Position(float x, float y) : _x(x), _y(y) {}

float Position::getX() const { return _x; }
float Position::getY() const { return _y; }

void Position::setX(float x) { _x = x; }
void Position::setY(float y) { _y = y; }
