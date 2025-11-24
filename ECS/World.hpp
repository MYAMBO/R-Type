/*
** EPITECH PROJECT, 2025
** bs
** File description:
** World
*/

#pragma once

#include <memory>
#include <vector>

#include "Entity/Entity.hpp"
#include "System/System.hpp"

class World {
    public:
        World() = default;
        ~World() = default;

        std::shared_ptr<Entity> createEntity(void);

        template<typename T>
        std::vector<std::shared_ptr<Entity>> getAllEntitiesWithComponent() const;

        template<typename T, typename ... Args>
        std::shared_ptr<T> addSystem(Args&&... args);

    private:
        std::vector<std::shared_ptr<Entity>> _entities;
        std::vector<std::shared_ptr<System>> _systems;
};

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
