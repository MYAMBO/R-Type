/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Damage
*/

#include "Damage.hpp"

/**
 * @brief Constructs a new Damage component with the number of damages.
 * @param damage Is the number of damage point.
*/
Damage::Damage(int damage) : _damage(damage)
{
}

/**
 * @brief Update the number of damages of an entity.
 * @param damage is the new value of damage point.
*/
void Damage::setDamage(const int damage)
{
    _damage = damage;
}

/**
 * @brief method used to get the damage value.
 * @return the damage value.
*/
int Damage::getDamage() const
{
    return _damage;
}