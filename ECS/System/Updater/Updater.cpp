/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Updater
*/

#include "Updater.hpp"

#include "Scale.hpp"
#include "Sprite.hpp"
#include "Sprite.hpp"
#include "Updater.hpp"
#include "Position.hpp"
#include "Rotation.hpp"
#include "Animator.hpp"
#include <SFML/System/Angle.hpp>

/**
* @brief Construct a new Updater:: Updater object
*/
Updater::Updater()
{
}

/**
* @brief Update the world by updating all entities' components
* @param dt Delta time since last update
* @param w Reference to the world containing entities and
*/
void Updater::update(const float& dt, World &w)
{
    updateSprites(dt, w);
    updateAnimations(dt, w);
}

/**
* @brief Update the sprites of all entities if they have it in the world
* @param dt Delta time since last update
* @param w Reference to the world containing entities and components
*/
void Updater::updateSprites(const float& dt, World &w)
{
    for (auto &entity : w.getAllEntitiesWithComponent<Sprite>()) {
        auto spriteComp = entity->getComponent<Sprite>();
        if (!spriteComp) {
            continue; 
        }
        auto sprite = spriteComp->getSprite();

        auto scaleComp = entity->getComponent<Scale>();
        auto posComp   = entity->getComponent<Position>();
        auto rotComp   = entity->getComponent<Rotation>();
        if (scaleComp) {
            float s = scaleComp->getScale();
            sprite->setScale({s, s});
        }
        if (posComp)
            sprite->setPosition({posComp->getX(), posComp->getY()});
        if (rotComp)
            sprite->setRotation(sf::degrees(rotComp->getRotation()));
    }
}

void Updater::updateAnimations(const float &dt, World &w)
{
    for (auto &entity : w.getAllEntitiesWithComponent<Animator>()) {
        auto anim = entity->getComponent<Animator>();
        auto spriteComp = entity->getComponent<Sprite>();
        if (!anim || !spriteComp)
            continue;
        auto sprite = spriteComp->getSprite();
        anim->setCurrentTime(anim->getCurrentTime() + dt);
        if (anim->getCurrentTime() >= anim->getFrameRate()) {
            anim->setCurrentTime(0.f);
            anim->setCurrentFrame(anim->getCurrentFrame() + 1);
        }
        sprite->setTextureRect(anim->getFrameRect());
    }
}
