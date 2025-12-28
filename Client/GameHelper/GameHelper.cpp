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
 * @brief Retrieves an entity by its ID from the world.
 *
 * @param world The world containing entities and components.
 * @param id The ID of the entity to retrieve.
 * @return A shared pointer to the Entity component, or nullptr if not found.
 */
std::shared_ptr<Entity> GameHelper::getEntityById(World &world, uint64_t id)
{
    for (const auto& entity : world.getAllEntitiesWithComponent<Tag>()) {
        if (entity->getId() == id) {
            return entity;
        }
    }
    //std::cerr << "Entity with id " << id << " not found." << std::endl;
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
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../sprites/r-typesheet42.gif"));
    enemy->addComponent<Animator>(2, 1, 3.0f, 0, 0, 33, 19, 33, 0);
    enemy->addComponent<Scale>(2.f);
    enemy->addComponent<Scene>(1);
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(33.0f, 19.0f);
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
        if (entity->getComponent<Group>()->getId() == groupId) {
            members.push_back(entity);
        }
    }
    return members;
}