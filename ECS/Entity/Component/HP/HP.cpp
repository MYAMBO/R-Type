/*
** EPITECH PROJECT, 2025
** bs
** File description:
** HP
*/

#include "HP.hpp"

/**
 * @brief Constructs a new HP component with specified maximum HP.
*/
HP::HP(int maxHp) : _hp(maxHp), _maxHp(maxHp) {}

/**
 * @brief Sets the current HP value.
*/
void HP::setHP(unsigned int hp)
{
    _hp = hp;
}

/**
 * @brief Gets the current HP value.
*/
unsigned int HP::getHP() const
{
    return _hp;
}
