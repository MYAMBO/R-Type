/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GameHelper
*/

#include "Tag.hpp"
#include "Group.hpp"
#include "GameHelper.hpp"
#include "BoxCollider.hpp"

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