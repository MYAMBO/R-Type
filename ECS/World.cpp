/*
** EPITECH PROJECT, 2025
** bs
** File description:
** World
*/

#include <memory>
#include <vector>

#include "World.hpp"
#include "Entity.hpp"

std::shared_ptr<Entity> World::createEntity()
{
    auto entity = std::make_shared<Entity>();
    _entities.push_back(entity);
    return entity;
}

template<typename T, typename ... Args>
std::shared_ptr<T> World::addSystem(Args&&... args)
{
    static_assert(std::is_base_of<System, T>::value, "T must be derived from System");
    auto comp = std::make_shared<T>(std::forward<Args>(args) ...);
    _systems.push_back(comp);
    return comp;
}
