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
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity.hpp"
#include "System.hpp"

/**
 * @brief World-class that manages entities and systems in the ECS architecture.
 *
 * The World class is responsible for creating and storing entities,
 * as well as managing the systems that operate on those entities.
*/
class World {
    public:
        World();
        ~World();

        std::shared_ptr<Entity> createEntity();

        template<typename T>
        [[nodiscard]] std::vector<std::shared_ptr<Entity>> getAllEntitiesWithComponent() const;

        template<typename T>
        [[nodiscard]] std::vector<std::shared_ptr<Entity>> getAllEntitiesWithComponents() const;

        template<typename T, typename ... Args>
        std::shared_ptr<T> addSystem(Args&&... args);

        void manageSystems();

        void setEvent(const sf::Event& event);
        [[nodiscard]] sf::Event& getEvent();

        void setDeltaTime(const float& dt);
        [[nodiscard]] float getDeltaTime() const;

        void setCurrentScene(int scene);
        [[nodiscard]] int getCurrentScene() const;

        void setWindow(sf::RenderWindow& window);
        [[nodiscard]] sf::RenderWindow* getWindow() const;
        
        template<typename T>
        std::shared_ptr<T> getSystem() const;

        void killEntity(std::size_t id);
    private:
        float _deltaTime;
        sf::Event _event;
        int _currentScene = 1;
        sf::RenderWindow *_window = nullptr;
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
    static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");
    std::vector<std::shared_ptr<Entity>> entitiesWithComponent;

    for (const auto& entity : _entities)
        if (auto component = entity->getComponent<T>())
            entitiesWithComponent.push_back(entity);
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
    static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");
    std::vector<std::shared_ptr<Entity>> entitiesWithComponent;
    for (const auto& entity : _entities)
        if (auto component = entity->getComponent<T>())
            entitiesWithComponent.push_back(entity);
    return entitiesWithComponent;
}

/**
 * @brief Retrieves a system of a specific type from the world.
 *
 * @tparam T The type of the system to retrieve. Must be derived from System.
 * @return A shared pointer to the system if found, nullptr otherwise.
 */
template<typename T>
std::shared_ptr<T> World::getSystem() const
{
    static_assert(std::is_base_of_v<System, T>, "T must be derived from System");
    for (const auto& system : _systems)
        if (std::shared_ptr<T> sysType = std::dynamic_pointer_cast<T>(system))
            return sysType;
    return nullptr;
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
    static_assert(std::is_base_of_v<System, T>, "T must be derived from System");
    auto comp = std::make_shared<T>(std::forward<Args>(args) ...);
    _systems.push_back(comp);
    return comp;
}

#endif /* !WORLD_HPP_ */