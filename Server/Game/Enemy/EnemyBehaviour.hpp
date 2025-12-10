/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EnemyBehaviour
*/

#ifndef R_TYPE_ENEMY_H
    #define R_TYPE_ENEMY_H

#include "World.hpp"
#include "Position.hpp"

class EnemyBehaviour : public Component
{
    public:
        explicit EnemyBehaviour(const Entity& entity);
        ~EnemyBehaviour() override = default;

        void move() const;
    private:
        std::shared_ptr<Position> _pos;
};

#endif //R_TYPE_ENEMY_H