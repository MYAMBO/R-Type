/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Draw
*/

#include "Draw.hpp"
#include "Sprite.hpp"

void Draw::update(const float& dt, World &w)
{
    (void) dt;
    auto entities = w.getAllEntitiesWithComponent<Sprite>();
    for (auto& entity : entities) {
        auto objectComponent = entity->getComponent<Sprite>();
        _window.draw(*objectComponent->getSprite());
    }
}
