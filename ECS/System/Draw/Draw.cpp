/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Draw
*/

#include "Draw.hpp"
#include "../../Entity/Component/Sprite/Sprite.hpp"

/**
 * @brief Updates the draw system by rendering all entities with a Sprite component.
 *
 * @param dt The delta time since the last update.
 * @param w The world containing the entities to be drawn.
 */
void Draw::update(const float& dt, World &w)
{
    (void) dt;
    auto entities = w.getAllEntitiesWithComponents<Sprite>();
    for (auto& entity : entities) {
        auto objectComponent = entity->getComponent<Sprite>();
        _window.draw(*objectComponent->getSprite());
    }
}
