/*
** EPITECH PROJECT, 2025
** bs
** File description:
** HP
*/

#include "HP.hpp"

/**
 * @brief Constructs a new HP component with specified maximum HP.
 * @param maxHp The maximum HP value for the component.
*/
HP::HP(int maxHp)
    : _hp(maxHp), _maxHp(maxHp)
{
}

/**
 * @brief Sets the current HP value.
 * @param hp The new HP value to set.
*/
void HP::setHP(unsigned int hp)
{
    _hp = hp;
}

/**
 * @brief Gets the current HP value.
 * @return The current HP value as an unsigned integer.
*/
unsigned int HP::getHP() const
{
    return _hp;
}

/**
 * @brief Gets the maximum HP value.
 * @return The maximum HP value as an unsigned integer.
*/
unsigned int HP::getMaxHP() const
{
    return _maxHp;
}

/**
 * @brief Sets the maximum HP value.
 * @param maxHp The new maximum HP value to set.
*/
void HP::setMaxHP(unsigned int maxHp)
{
    _maxHp = maxHp;
}