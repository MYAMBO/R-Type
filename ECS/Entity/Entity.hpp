/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Entity
*/

#pragma once

#include <memory>
#include <vector>
#include <utility>
#include <cstddef>

#include "Component.hpp"

class Entity {
    public:
        Entity();
        ~Entity() = default;

        template<typename T, typename ... Args>
        void addComponent(Args&& ... args);

        template<typename T>
        std::shared_ptr<T> getComponent(void) const;
    private:
        std::size_t _id;
        std::vector<std::shared_ptr<Component>> _components;
};

template<typename T, typename ... Args>
void Entity::addComponent(Args&& ... args)
{
    auto comp = std::make_shared<T>(std::forward<Args>(args)...);
    _components.push_back(comp);
}

template<typename T>
std::shared_ptr<T> Entity::getComponent(void) const
{
    static_assert(std::is_base_of<Component, T>::value, "T must be a Component");
    for (const auto& comp : _components) {
        std::shared_ptr<T> comType = std::dynamic_pointer_cast<T>(comp);
        if (comType)
            return comType;
    }
    return nullptr;
}
