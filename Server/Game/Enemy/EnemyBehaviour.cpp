/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EnemyBehaviour
*/

#include "EnemyBehaviour.hpp"

EnemyBehaviour::EnemyBehaviour(const Entity& entity)
{
    _pos = entity.getComponent<Position>();
}

void EnemyBehaviour::move() const
{
    _pos->setX(_pos->getX() + 10);
    _pos->setY(_pos->getY() + 10);
}
