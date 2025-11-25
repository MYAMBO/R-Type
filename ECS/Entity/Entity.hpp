/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_

#include <memory>
#include <vector>
#include <utility>
#include <cstddef>

#include "Component/Component.hpp"

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

/**
 * @brief Adds a new component of type T to the entity.
 *
 * @tparam T The type of the component to add. Must be derived from Component.
 * @tparam Args The types of the arguments to pass to the component's constructor.
 * @param args The arguments to pass to the component's constructor.
 */
template<typename T, typename ... Args>
void Entity::addComponent(Args&& ... args)
{
    auto comp = std::make_shared<T>(std::forward<Args>(args)...);
    _components.push_back(comp);
}

/**
 * @brief Retrieves a component of type T from the entity.
 *
 * @tparam T The type of the component to retrieve. Must be derived from Component.
 * @return A shared pointer to the component if found, nullptr otherwise.
 */
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

#endif /* !ENTITY_HPP_ */