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
#include "Group.hpp"
#include "Camera.hpp"
#include "Sprite.hpp"
#include "Position.hpp"
#include "Animator.hpp"
#include "GameHelper.hpp"
#include "BoxCollider.hpp"
#include "Damage.hpp"
#include "Velocity.hpp"

/**
 * @brief Retrieves the main camera from the world.
 *
 * @param world The world containing entities and components.
 * @return A shared pointer to the main Camera component, or nullptr if not found.
 */
std::shared_ptr<Camera> GameHelper::getMainCamera(World &world)
{
    for (const auto& entity : world.getAllEntitiesWithComponent<Camera>()) {
        if (!entity)
            continue;
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
        if (!entity)
            continue;
        auto tagComp = entity->getComponent<Tag>();
        if (tagComp && tagComp->getTag() == tag) {
            return entity;
        }
    }
    return nullptr;
}

/**
 * @brief Retrieves an entity by its ID from the world.
 *
 * @param world The world containing entities and components.
 * @param id The ID of the entity to retrieve.
 * @return A shared pointer to the Entity component, or nullptr if not found.
 */
std::shared_ptr<Entity> GameHelper::getEntityById(World &world, uint64_t id)
{
    for (const auto& entity : world.getAllEntitiesWithComponent<Tag>()) {
        if (!entity)
            continue;
        if (entity->getId() == id) {
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
    auto enemy = world.createEntity();
    enemy->addComponent<HP>(50);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet11.gif"));
    enemy->addComponent<Animator>(2, 6, 5.0f, 0, 0, 33, 30, 33, 0);
    enemy->addComponent<Scale>(2.f);
    enemy->addComponent<Scene>(1);
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
    enemy->addComponent<Velocity>(-2.0f, 0.0f);
}


/**
 * @brief Retrieves all entities belonging to a specific group from the world.
 *
 * @param world The world containing entities and components.
 * @param groupId The ID of the group to retrieve entities from.
 * @return A vector of shared pointers to the entities in the specified group.
 */
std::vector<std::shared_ptr<Entity>> GameHelper::getEntitiesByGroup(World &world, size_t groupId)
{
    std::vector<std::shared_ptr<Entity>> members;

    for (const auto& entity : world.getAllEntitiesWithComponent<Group>()) {
        if (!entity)
            continue;
        if (entity->getComponent<Group>()->getId() == groupId) {
            members.push_back(entity);
        }
    }
    return members;
}