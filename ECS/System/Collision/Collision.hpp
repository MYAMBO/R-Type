/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Collision
*/

#ifndef R_TYPE_COLLISION_H
    #define R_TYPE_COLLISION_H

#include "System.hpp"
#include "Position.hpp"
#include "BoxCollider.hpp"
#include "World.hpp"
#include <iostream>


/**
 * @brief Updater system responsible for updating various components of entities.
 *
 * This system handles the updating of the checks of collisions between
 * Entities.
*/
class Collision : public System {

    public:
        Collision() = default;
        ~Collision() override = default;

        void update(const float& dt, World &w) override;
        [[nodiscard]] static bool checkCollision(const BoxCollider &aB, const Position &aP,
                            const BoxCollider &bB, const Position &bP);

    private:
        static void handleCollisionDamage(const std::shared_ptr<Entity> &a,
                                     const std::shared_ptr<Entity> &b);
        static void applyDamage(const std::shared_ptr<Entity> &attacker,
                           const std::shared_ptr<Entity> &target);
};


#endif //R_TYPE_COLLISION_H