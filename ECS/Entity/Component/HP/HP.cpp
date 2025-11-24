/*
** EPITECH PROJECT, 2025
** bs
** File description:
** HP
*/

#include "HP.hpp"

HP::HP(int maxHp) : _hp(maxHp), _maxHp(maxHp) {}

void HP::setHP(unsigned int hp)
{
    _hp = hp;
}

unsigned int HP::getHP() const
{
    return _hp;
}
