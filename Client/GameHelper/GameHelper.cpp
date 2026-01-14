/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GameHelper
*/

#include "HP.hpp"
#include "Tag.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include "Group.hpp"
#include "Camera.hpp"
#include "Sprite.hpp"
#include "Position.hpp"
#include "Animator.hpp"
#include "GameHelper.hpp"
#include "BoxCollider.hpp"
#include "Damage.hpp"
#include "Velocity.hpp"

/**
 * @brief Retrieves the main camera from the world.
 *
 * @param world The world containing entities and components.
 * @return A shared pointer to the main Camera component, or nullptr if not found.
 */
std::shared_ptr<Camera> GameHelper::getMainCamera(World &world)
{
    for (const auto& entity : world.getAllEntitiesWithComponent<Camera>()) {
        if (!entity)
            continue;
        auto tagComp = entity->getComponent<Tag>();
        if (tagComp && tagComp->getTag() == "main_camera") {
            return entity->getComponent<Camera>();
        }
    }
    return nullptr;
}

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
 * @brief Creates a basic enemy entity in the world at the specified position.
 *
 * @param world The world to create the enemy in.
 * @param x The x-coordinate of the enemy's position.
 * @param y The y-coordinate of the enemy's position.
*/
void GameHelper::createBasicEnemy(World &world, float x, float y, int entityId)
{
    auto enemy = world.createEntity(entityId);
    enemy->addComponent<HP>(50);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet11.gif"));
    enemy->addComponent<Animator>(2, 6, 5.0f, 0, 0, 33, 30, 33, 0);
    enemy->addComponent<Scale>(2.f);
    enemy->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
}


void GameHelper::createSinusEnemy(World &world, float x, float y, int entityId)
{
    auto enemy = world.createEntity(entityId);
    enemy->addComponent<HP>(50);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet11.gif"));
    enemy->addComponent<Animator>(2, 6, 5.0f, 0, 0, 33, 30, 33, 0);
    enemy->addComponent<Scale>(2.f);
    enemy->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
}

void GameHelper::createShootingEnemy(World &world, float x, float y, int entityId)
{
    auto enemy = world.createEntity(entityId);
    enemy->addComponent<HP>(50);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet11.gif"));
    enemy->addComponent<Animator>(2, 6, 5.0f, 0, 0, 33, 30, 33, 0);
    enemy->addComponent<Scale>(2.f);
    enemy->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
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

sf::Color GameHelper::hueToRGB(float hue)
{
    float s = 1.0f;
    float v = 1.0f;
    int i = static_cast<int>(hue / 60.0f) % 6;
    float f = (hue / 60.0f) - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);
    float r, g, b;
    
    switch (i) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
        default: r = g = b = 0; break;
    }

    return sf::Color(
        static_cast<std::uint8_t>(r * 255), 
        static_cast<std::uint8_t>(g * 255), 
        static_cast<std::uint8_t>(b * 255)
    );
}

/**
 * @brief Retrieves the color transformation matrix for a given color blindness mode.
 *
 * @param mode The color blindness mode.
 * @return A 3x3 color transformation matrix.
 */
ColorMatrix GameHelper::getColorMatrix(ColorBlindMode mode) {
    switch (mode) {
        case ColorBlindMode::Protanopia:
            return {{0.567f, 0.433f, 0.0f}, {0.558f, 0.442f, 0.0f}, {0.0f, 0.242f, 0.758f}};
        case ColorBlindMode::Deuteranopia:
            return {{0.625f, 0.375f, 0.0f}, {0.70f, 0.30f, 0.0f}, {0.0f, 0.30f, 0.70f}};
        case ColorBlindMode::Tritanopia:
            return {{0.95f, 0.05f, 0.0f}, {0.0f, 0.433f, 0.567f}, {0.0f, 0.475f, 0.525f}};
        case ColorBlindMode::Achromatopsia:
            return {{0.299f, 0.587f, 0.114f}, {0.299f, 0.587f, 0.114f}, {0.299f, 0.587f, 0.114f}};
        default:
            return {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
    }
}