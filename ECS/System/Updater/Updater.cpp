/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Updater
*/

#include "Updater.hpp"

#include "Tag.hpp"
#include "Scale.hpp"
#include "Sprite.hpp"
#include "Script.hpp"
#include "Camera.hpp"
#include "Updater.hpp"
#include "Velocity.hpp"
#include "Position.hpp"
#include "Rotation.hpp"
#include "Animator.hpp"
#include <SFML/System/Angle.hpp>

/**
* @brief Construct a new Updater:: Updater object
*/
Updater::Updater() = default;

/**
* @brief Update the world by updating all entities' components
* @param dt Delta time since last update
* @param w Reference to the world containing entities and
*/
void Updater::update(const float& dt, World &w)
{
    updatePositions(dt, w);
    updateCameras(dt, w);
    updateScripts(dt, w);
    updateAnimations(dt, w);
    updateSprites(dt, w);
}


/**
* @brief Update the positions of all entities if they have it in the world
 * @param dt Delta time since last update
 * @param w Reference to the world containing entities and components
 */
void Updater::updatePositions(const float& dt, World &w)
{
    for (const auto &entity : w.getAllEntitiesWithComponent<Position>()) {
        const auto posComp = entity->getComponent<Position>();
        const auto velComp = entity->getComponent<Velocity>();
        if (posComp && velComp) {
            posComp->setX(posComp->getX() + velComp->getVelocityX() * dt);
            posComp->setY(posComp->getY() + velComp->getVelocityY() * dt);
        } else if (posComp) {
            posComp->setX(posComp->getX());
            posComp->setY(posComp->getY());
        }
    }
}

/**
* @brief Update the sprites of all entities if they have it in the world
* @param dt Delta time since last update
* @param w Reference to the world containing entities and components
*/
void Updater::updateSprites(const float& dt, const World &w)
{
    for (const auto &entity : w.getAllEntitiesWithComponent<Sprite>()) {
        const auto spriteComp = entity->getComponent<Sprite>();
        if (!spriteComp) {
            continue; 
        }
        const auto sprite = spriteComp->getSprite();
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

/**
* @brief Update the animations of sprite of all entities if they have it in the world
* @param dt Delta time since last update
* @param w Reference to the world containing entities and components
*/
void Updater::updateAnimations(const float &dt, const World &w)
{
    for (const auto &entity : w.getAllEntitiesWithComponent<Animator>()) {
        const auto anim = entity->getComponent<Animator>();
        const auto spriteComp = entity->getComponent<Sprite>();
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

/**
* @brief Update the camera of all entities if they have it in the world
* @param dt Delta time since last update
* @param w Reference to the world containing entities and components
*/
void Updater::updateCameras(const float &dt, const World &w)
{
    (void)dt;
    for (auto &entity : w.getAllEntitiesWithComponent<Camera>()) {
        auto cameraComp = entity->getComponent<Camera>();
        if (!cameraComp)
            continue; 
        auto posComp = entity->getComponent<Position>();
        if (posComp)
            cameraComp->setPosition({posComp->getX(), posComp->getY()});
        w.getWindow()->setView(cameraComp->getView());
    }
}

/**
* @brief Update the scripts of all entities if they have it in the world
* @param dt Delta time since last update
* @param w Reference to the world containing entities and components
*/
void Updater::updateScripts(const float &dt, World &w)
{
    (void)dt;
    for (auto &entity : w.getAllEntitiesWithComponent<Script>()) {
        auto scriptComp = entity->getComponent<Script>();
        if (!scriptComp || !scriptComp->getScript())
            continue; 
        scriptComp->getScript()(entity->getId(), w);
    }
}