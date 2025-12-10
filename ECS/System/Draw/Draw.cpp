/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Draw
*/

#include "Draw.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"

/**
 * @brief Updates the draw system by rendering all entities with a Sprite component.
 *
 * @param dt The delta time since the last update.
 * @param w The world containing the entities to be drawn.
 */
void Draw::update(const float& dt, World &w)
{
    (void) dt;
    const auto entities = w.getAllEntitiesWithComponent<Sprite>();
    for (auto& entity : entities) {
        const auto objectComponent = entity->getComponent<Sprite>();
        const auto sceneComponent = entity->getComponent<Scene>();
        if (!objectComponent || !sceneComponent)
            continue;
        if (sceneComponent->getScene() != w.getCurrentScene())
            continue;
        w.getWindow()->draw(*objectComponent->getSprite());
    }
}
