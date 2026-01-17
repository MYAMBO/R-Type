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

#include <map>

/**
 * @brief Constructs a new World object.
 */
World::World()
    : _event(sf::Event::FocusLost{}) 
{
}

/**
 * @brief destroys the World object.
 */
World::~World()
{
    std::lock_guard<std::mutex> lock(_entitiesMutex);
    _entities.clear();
    _systems.clear();
}

/**
 * @brief Creates a new entity and adds it to the world.
 *
 * @return A shared pointer to the newly created entity.
 */
std::shared_ptr<Entity> World::createEntity(uint64_t id)
{
    std::lock_guard<std::mutex> lock(_entitiesMutex);
    auto entity = std::make_shared<Entity>(id);
    _entities.push_back(entity);
    return entity;
}

/**
 * @brief Manages all systems and profiles their execution time.
 */
void World::manageSystems()
{
    static sf::Clock reportClock;
    static std::map<std::string, float> accumulatedTime;

    for (const auto& system : _systems) {
        // 1. Démarrer le chrono pour ce système
        sf::Clock systemClock;

        // 2. Exécuter le système
        system->update(this->getDeltaTime(), *this);

        // 3. Calculer le temps passé (en microsecondes pour plus de précision)
        float elapsed = systemClock.getElapsedTime().asMicroseconds();
        
        // On stocke le nom de la classe du système (ex: "Draw", "Collision")
        // Note: typeid().name() peut être un peu cryptique selon le compilateur, 
        // mais c'est le plus simple sans modifier tes classes.
        accumulatedTime[typeid(*system).name()] += elapsed;
    }

    // 4. Afficher le rapport toutes les secondes (environ 30 ou 60 frames)
    if (reportClock.getElapsedTime().asSeconds() >= 1.0f) {
        std::cout << "\n--- [SYSTEMS PERF REPORT (total for 1s)] ---" << std::endl;
        for (auto const& [name, time] : accumulatedTime) {
            // Affichage en millisecondes pour la lisibilité
            std::cout << "  " << name << " : " << (time / 1000.f) << " ms" << std::endl;
        }
        std::cout << "--------------------------------------------" << std::endl;
        
        // Reset pour la seconde suivante
        accumulatedTime.clear();
        reportClock.restart();
    }
}

/**
 * @brief Retrieves the current SFML event.
 *
 * @return A reference to the current SFML event.
 */
sf::Event& World::getEvent()
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
float World::getDeltaTime() const
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
sf::RenderWindow* World::getWindow() const
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
void World::setCurrentScene(const int scene)
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
void World::killEntity(uint64_t id)
{
    std::lock_guard<std::mutex> lock(_entitiesMutex);
    auto it = std::remove_if(_entities.begin(), _entities.end(),
        [id](const std::shared_ptr<Entity>& entity) {
            return entity->getId() == id;
        });
    if (it != _entities.end()) {
        _entities.erase(it, _entities.end());
    }
}