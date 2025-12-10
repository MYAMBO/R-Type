/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#include "HP.hpp"
#include "Tag.hpp"
#include "Script.hpp"
#include "Updater.hpp"
#include "Position.hpp"
#include "ServerGame.hpp"
#include "BoxCollider.hpp"
#include "Enemy/EnemyBehaviour.hpp"

/**
 * @brief Constructs a new Game object.
 *
 * Initializes the game.
 */
ServerGame::ServerGame()
{
    _world.addSystem<Updater>();
    _world.setDeltaTime(1.f);
}

static std::string get_client_informations()
{
    return std::string("hello");
}

/**
 * @brief Runs the main game loop.
 *
 * This function initializes the game world, creates entities,
 * and handles the main event loop.
 */
void ServerGame::run()
{
    while (true) {
        _world.manageSystems();
        std::string info = get_client_informations();

    }
}

/**
 * @brief Creates the player entity.
 *
 * This function initializes the player entity with necessary components.
 */
void ServerGame::createPlayer()
{
    const auto player = _world.createEntity();
    player->addComponent<HP>(100);
    player->addComponent<Position>(75.0f, 75.0f);
    player->addComponent<BoxCollider>((sf::Vector2f){10.f, 10.f});
    player->addComponent<Tag>("player");
}

static void EnemyMovement(int entityId, World &world)
{
    const auto entity = world.getAllEntitiesWithComponent<Tag>()[entityId];
    const auto pos = entity->getComponent<Position>();

    pos->setX(pos->getX() + 10);
    pos->setY(pos->getY() + 10);
}

/**
 * @brief Creates the player entity.
 *
 * This function initializes the player entity with necessary components.
 */
void ServerGame::createEnemy()
{
    const auto enemy = _world.createEntity();
    enemy->addComponent<HP>(100);
    enemy->addComponent<Position>(150.0f, 150.0f);
    enemy->addComponent<BoxCollider>((sf::Vector2f){10.f, 10.f});
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<Script>(EnemyMovement);
}
