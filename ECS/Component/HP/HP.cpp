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
HP::HP(const int maxHp)
    : _hp(maxHp), _maxHp(maxHp), _isAlive(true)
{
}

/**
 * @brief Sets the current HP value.
 * @param hp The new HP value to set.
*/
void HP::setHP(const unsigned int hp)
{
    if (_hp == 0)
        return;
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
void HP::setMaxHP(const unsigned int maxHp)
{
    _maxHp = maxHp;
}

/**
 * @brief Gets the isAlive value.
 * @return if the current player is alive or not.
*/
bool HP::isAlive() const
{
    return _isAlive;
}

/**
 * @brief change the alive value.
 * @param alive update the current alive value.
*/
void HP::setAlive(const bool alive)
{
    _isAlive = alive;
}