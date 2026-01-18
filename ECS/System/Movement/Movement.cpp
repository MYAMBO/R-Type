/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Movement
*/

#include "Movement.hpp"

#include "Position.hpp"
#include "Velocity.hpp"
#include "Scene.hpp"

/**
* @brief Update the positions of all entities if they have it in the world
 * @param dt Delta time since last update
 * @param w Reference to the world containing entities and components
 */
void Movement::update(const float& dt, World &w)
{
    for (const auto &entity : w.getAllEntitiesWithComponent<Position>()) {
        const auto posComp = entity->getComponent<Position>();
        const auto velComp = entity->getComponent<Velocity>();
        const auto sceneComp = entity->getComponent<Scene>();
        if (sceneComp && sceneComp->getScene() != w.getCurrentScene())
            continue;
        if (!posComp)
            continue;
        if (posComp && velComp) {
            posComp->setX(posComp->getX() + velComp->getVelocityX() * dt);
            posComp->setY(posComp->getY() + velComp->getVelocityY() * dt);
        } else if (posComp && !velComp) {
            posComp->setX(posComp->getX());
            posComp->setY(posComp->getY());
        }
    }
}

