/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Velocity
*/

#include "Velocity.hpp"

Velocity::Velocity(float velocity) : _velocity(velocity)
{
}

float Velocity::getVelocity() const
{
    return _velocity;
}

void Velocity::setVelocity(float velocity)
{
    _velocity = velocity;
}


