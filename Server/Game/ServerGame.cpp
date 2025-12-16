/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#include "HP.hpp"
#include "Tag.hpp"
#include "Packet.hpp"
#include "Script.hpp"
#include "Updater.hpp"
#include "Position.hpp"
#include "ServerGame.hpp"
#include "BoxCollider.hpp"

/**
 * @brief Constructs a new Game object.
 *
 * Initializes the game.
 */
ServerGame::ServerGame(IGameNetwork& network) : _network(network)
{
    _world.addSystem<Updater>();
    _world.setDeltaTime(1.f);
}

/**
 * @brief Runs the main game loop.
 *
 * This function initializes the game world, creates entities,
 * and handles the main event loop.
 */
void ServerGame::run()
{
    createWave();
    Packet packet;

    packet.dead(1);

    while (true) {
        _world.manageSystems();
        _network.sendPacket(packet);
    }
}

/**
 * @brief Creates the player entity.
 *
 * @param x The x position of player.
 * @param y The y position of player.
 * This function initializes the player entity with necessary components.
 */
void ServerGame::createPlayer(const float x, const float y)
{
    const auto player = _world.createEntity();
    player->addComponent<HP>(100);
    player->addComponent<Position>(x, y);
    player->addComponent<BoxCollider>((sf::Vector2f){10.f, 10.f});
    player->addComponent<Tag>("player");
    Packet packet;
    packet.positionSpawn(player->getId(), Player, x, y);
    // call function to send packet
}

/**
 * @brief define the movement of an enemy.
 *
 * @param entityId the ID if the entity.
 * @param world the world where all entity are contains.
 */
static void EnemyMovement(const int entityId, const World &world)
{
    const auto entity = world.getAllEntitiesWithComponent<Tag>()[entityId];

    if (const auto pos = entity->getComponent<Position>(); pos->getX() > 500) {
        pos->setX(pos->getX() - 10 * world.getDeltaTime());
        Packet packet;
        packet.positionSpawn(entity->getId(), None, pos->getX(), pos->getY());
        // call function to send packet
    }
}

/**
 * @brief Creates the player entity.
 *
 * @param x The x position of the enemy.
 * @param y The y position of the enemy.
 * This function initializes the player entity with necessary components.
 */
void ServerGame::createEnemy(const float x, const float y)
{
    const auto enemy = _world.createEntity();
    enemy->addComponent<HP>(100);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<BoxCollider>((sf::Vector2f){10.f, 10.f});
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<Script>(EnemyMovement);
// call function to send packet
    Packet packet;
    packet.positionSpawn(enemy->getId(), Enemy, x, y);
    // call function to send packet
}

/**
 * @brief Create a wave of enemies
 */
void ServerGame::createWave()
{
    for (auto i = 0; i < 10; ++i)
        createEnemy(1920 + i * 50, 940);
}

/**
 * @brief define the movement of a bullet.
 *
 * @param entityId the ID if the entity.
 * @param world the world where all entity are contains.
 */
static void BulletMovement(const int entityId, World &world)
{
    const auto entity = world.getAllEntitiesWithComponent<Tag>()[entityId];
    const auto pos = entity->getComponent<Position>();
    Packet packet;

    if (entity->getComponent<BoxCollider>()->isTrigger()) {
        // check collisions with enemies
    }
    if (pos->getX() > 3000) {
        world.killEntity(entity->getId());
        packet.dead(entity->getId());
    } else {
        pos->setX(pos->getX() + 10 * world.getDeltaTime());
        packet.positionSpawn(entity->getId(), None, pos->getX(), pos->getY());
    }
    // call function to send packet
}

/**
 * @brief Create a bullet.
 *
 * @param x The x position of the bullet on apparition.
 * @param y The y position of the bullet on apparition.
 */
void ServerGame::createBullet(const float x, const float y)
{
    const auto bullet = _world.createEntity();

    bullet->addComponent<Position>(x, y);
    bullet->addComponent<BoxCollider>((sf::Vector2f){5.f, 5.f});
    bullet->addComponent<Tag>("bullet");
    bullet->addComponent<Script>(BulletMovement);
    Packet packet;
    packet.positionSpawn(bullet->getId(), Bullet, x, y);
    // call function to send packet
}

/**
 * @brief Create a new player when a client connect.
 */
void ServerGame::handleNewPlayer()
{
    createPlayer(300, 300);
}

/**
 * @brief check if the new position send by the client is valid and change it in server side.
 *
 * @param id The id of the player who is moving.
 * @param x The new x position of the player.
 * @param y The new y position of the player.
 */
void ServerGame::handleNewPlayerPosition(const int id, const float x, const float y) const
{
    const auto entity = _world.getAllEntitiesWithComponent<Tag>()[id];
    const auto pos = entity->getComponent<Position>();

    const auto distanceX = pos->getX() - x;
    const auto distanceY = pos->getY() - y;

    if (distanceX * distanceX + distanceY * distanceY <= 20.f) {
        pos->setX(x);
        pos->setY(y);
    }

    Packet packet;
    packet.positionSpawn(id, None, x, y);
    // call function to send packet
}

/**
 * @brief Create a bullet at the place of the player who is shooting.
 *
 * @param id The id of the player who is shooting.
 */
void ServerGame::handleShoot(const int id)
{
    const auto entity = _world.getAllEntitiesWithComponent<Tag>()[id];
    const auto pos = entity->getComponent<Position>();

    createBullet(pos->getX(), pos->getY());
}
