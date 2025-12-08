/*
** EPITECH PROJECT, 2025
** bs
** File description:
** World
*/

#include <memory>
#include <vector>
#include <algorithm>

#include "World.hpp"
#include "Entity.hpp"


/**
 * @brief Constructs a new World object.
 */
World::World()
    : _event(sf::Event::FocusLost{}) 
{
    sf::Clock clock;
    _deltaTime = clock.restart().asSeconds();
}

/**
 * @brief destroys the World object.
 */
World::~World()
{
    _entities.clear();
    _systems.clear();
}

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
 * @brief Manages all systems in the world by calling their update methods.
 */
void World::manageSystems(void)
{
    for (const auto& system : _systems) {
        system->update(this->getDeltaTime(), *this);
    }
}

/**
 * @brief Retrieves the current SFML event.
 *
 * @return A reference to the current SFML event.
 */
sf::Event& World::getEvent(void)
{
    return _event;
}

/**
 * @brief Sets the current SFML event.
 *
 * @param event The SFML event to set.
 */
void World::setEvent(const sf::Event& event)
{
    _event = event;
}

/**
 * @brief Retrieves the current delta time.
 *
 * @return The current delta time.
 */
float World::getDeltaTime(void) const
{
    return _deltaTime;
}

/**
 * @brief Sets the current delta time.
 *
 * @param dt The delta time to set.
 */
void World::setDeltaTime(const float& dt)
{
    _deltaTime = dt;
}

/**
 * @brief Retrieves the render window.
 *
 * @return A reference to the render window.
 */
sf::RenderWindow* World::getWindow(void) const
{
    return _window;
}

/**
 * @brief Sets the render window.
 *
 * @param window The render window to set.
 */
void World::setWindow(sf::RenderWindow& window)
{
    _window = &window;
}

/**
 * @brief Sets the current scene.
 *
 * @param scene The scene to set.
 */
void World::setCurrentScene(int scene)
{
    _currentScene = scene;
}

/**
 * @brief Retrieves the current scene.
 *
 * @return The current scene.
 */
int World::getCurrentScene() const
{
    return _currentScene;
}

/**
 * @brief kill an entity by its ID.
* @param id The ID of the entity to kill.
*/
void World::killEntity(size_t id)
{
    auto it = std::remove_if(_entities.begin(), _entities.end(),
        [id](const std::shared_ptr<Entity>& entity) {
            return entity->getId() == id;
        });
    if (it != _entities.end()) {
        _entities.erase(it, _entities.end());
    }
}