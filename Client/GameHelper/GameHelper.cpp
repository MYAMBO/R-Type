/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GameHelper
*/

#include "HP.hpp"
#include "Tag.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Sprite.hpp"
#include "Position.hpp"
#include "Animator.hpp"
#include "GameHelper.hpp"

/**
 * @brief Retrieves the main camera from the world.
 *
 * @param world The world containing entities and components.
 * @return A shared pointer to the main Camera component, or nullptr if not found.
 */
std::shared_ptr<Camera> GameHelper::getMainCamera(World &world)
{
    for (const auto& entity : world.getAllEntitiesWithComponent<Tag>()) {
        auto tagComp = entity->getComponent<Tag>();
        if (tagComp && tagComp->getTag() == "main_camera") {
            return entity->getComponent<Camera>();
        }
    }
    return nullptr;
}

/**
 * @brief Retrieves the main player from the world.
 *
 * @param world The world containing entities and components.
 * @return A shared pointer to the main Player component, or nullptr if not found.
 */
std::shared_ptr<Entity> GameHelper::getEntityByTag(World &world, const std::string &tag)
{
    for (const auto& entity : world.getAllEntitiesWithComponent<Tag>()) {
        auto tagComp = entity->getComponent<Tag>();
        if (tagComp && tagComp->getTag() == tag) {
            return entity;
        }
    }
    return nullptr;
}

/**
 * @brief Creates a basic enemy entity in the world at the specified position.
 *
 * @param world The world to create the enemy in.
 * @param x The x-coordinate of the enemy's position.
 * @param y The y-coordinate of the enemy's position.
*/
void GameHelper::createBasicEnemy(World &world, float x, float y)
{
    printf("Creating basic enemy at (%f, %f)\n", x, y);
    auto enemy = world.createEntity();
    enemy->addComponent<HP>(50);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../sprites/r-typesheet42.gif"));
    enemy->addComponent<Animator>(2, 3.0f, 0, 0, 33, 19, 33, 0);
    enemy->addComponent<Scale>(2.f);
    enemy->addComponent<Scene>(1);
    enemy->addComponent<Tag>("enemy");
}