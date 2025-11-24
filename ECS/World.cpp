/*
** EPITECH PROJECT, 2025
** bs
** File description:
** World
*/

#include <memory>
#include <vector>

#include "World.hpp"
#include "Entity/Entity.hpp"

/**
 * @brief Creates a new entity and adds it to the world.
 *
 * @return A shared pointer to the newly created entity.
 */
std::shared_ptr<Entity> World::createEntity()
{
    auto entity = std::make_shared<Entity>();
    _entities.push_back(entity);
    return entity;
}

/**
 * @brief Adds a new system to the world.
 *
 * @tparam T The type of the system to add. Must be derived from System.
 * @tparam Args The types of the arguments to pass to the system's constructor.
 * @param args The arguments to pass to the system's constructor.
 * @return A shared pointer to the newly added system.
 */
template<typename T, typename ... Args>
std::shared_ptr<T> World::addSystem(Args&&... args)
{
    static_assert(std::is_base_of<System, T>::value, "T must be derived from System");
    auto comp = std::make_shared<T>(std::forward<Args>(args) ...);
    _systems.push_back(comp);
    return comp;
}
