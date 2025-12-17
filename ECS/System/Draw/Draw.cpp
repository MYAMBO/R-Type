/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Draw
*/

#include <algorithm>

#include "Draw.hpp"
#include "Scene.hpp"
#include "Layer.hpp"
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
    auto entities = w.getAllEntitiesWithComponent<Sprite>();
    std::sort(entities.begin(), entities.end(), [](const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b) {
        auto layerAComp = a->getComponent<Layer>();
        auto layerBComp = b->getComponent<Layer>();
        int valA = 0;
        int valB = 0;
        if (!layerAComp)
            valA = 1;
        else
            valA = layerAComp->getLayerId();
        if (!layerBComp)
            valB = 1;
        else
            valB = layerBComp->getLayerId();
        return valA < valB;
    });

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