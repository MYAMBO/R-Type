/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TextSys
*/

#include "Text.hpp"
#include "TextSys.hpp"
#include "Rotation.hpp"
#include "Position.hpp"

void TextSystem::update(const float& dt, World &world)
{
    (void)dt;
    for (auto &entity : world.getAllEntitiesWithComponent<Text>()) {
        auto textComp = entity->getComponent<Text>();
        auto posComp = entity->getComponent<Position>();
        auto rotComp = entity->getComponent<Rotation>();

        if (!textComp)
            continue;
        if (posComp)
            textComp->getSfText().setPosition({posComp->getX(), posComp->getY()});
        if (rotComp)
            textComp->getSfText().setRotation(sf::degrees(rotComp->getRotation()));
    }
}