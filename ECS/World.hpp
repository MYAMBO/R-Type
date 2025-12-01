/*
** EPITECH PROJECT, 2025
** bs
** File description:
** World
*/

#ifndef WORLD_HPP_
    #define WORLD_HPP_

#include <memory>
#include <vector>

#include "Entity.hpp"
#include "System.hpp"

class World {
    public:
        World() = default;
        ~World() = default;

        std::shared_ptr<Entity> createEntity(void);

        template<typename T>
        [[nodiscard]] std::vector<std::shared_ptr<Entity>> getAllEntitiesWithComponent() const;

        template<typename T>
        [[nodiscard]] std::vector<std::shared_ptr<Entity>> getAllEntitiesWithComponents() const;

        template<typename T, typename ... Args>
        std::shared_ptr<T> addSystem(Args&&... args);

    private:
        std::vector<std::shared_ptr<Entity>> _entities;
        std::vector<std::shared_ptr<System>> _systems;
};

/**
 * @brief Retrieves all entities that have a specific component type.
 *
 * @tparam T The type of the component to check for. Must be derived from Component.
 * @return A vector of shared pointers to entities that have the specified component.
 */
template<typename T>
std::vector<std::shared_ptr<Entity>> World::getAllEntitiesWithComponent() const
{
    static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
    std::vector<std::shared_ptr<Entity>> entitiesWithComponent;

    for (const auto& entity : _entities) {
        auto component = entity->getComponent<T>();
        if (component)
            entitiesWithComponent.push_back(entity);
    }
    return entitiesWithComponent;
}


/**
 * @brief Retrieves all entities that have a specific component type.
 *
 * @tparam T The type of the component to check for. Must be derived from Component.
 * @return A vector of shared pointers to entities that have the specified component.
 */
template<typename T>
std::vector<std::shared_ptr<Entity>> World::getAllEntitiesWithComponents() const
{
    static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
    std::vector<std::shared_ptr<Entity>> entitiesWithComponent;
    for (const auto& entity : _entities) {
        auto component = entity->getComponent<T>();
        if (component)
            entitiesWithComponent.push_back(entity);
    }
    return entitiesWithComponent;
}

#endif /* !WORLD_HPP_ */