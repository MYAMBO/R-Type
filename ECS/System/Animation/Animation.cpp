/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Animation
*/

#include "Animation.hpp"

#include "Scene.hpp"
#include "Sprite.hpp"
#include "Animator.hpp"

#include <SFML/Graphics/Sprite.hpp>

/**
* @brief Update the animations of sprite of all entities if they have it in the world
* @param dt Delta time since last update
* @param w Reference to the world containing entities and components
*/
void Animation::update(const float &dt, World &w)
{
    for (const auto &entity : w.getAllEntitiesWithComponent<Animator>()) {
        const auto sceneComp = entity->getComponent<Scene>();
        const auto anim = entity->getComponent<Animator>();
        const auto spriteComp = entity->getComponent<Sprite>();

        if (!anim || !spriteComp || !sceneComp)
            continue;
        if (w.getCurrentScene() !=  sceneComp->getScene())
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