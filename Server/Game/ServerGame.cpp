/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#include <algorithm>

#include "HP.hpp"
#include "Tag.hpp"
#include "Server.hpp"
#include "Packet.hpp"
#include "Script.hpp"
#include "Updater.hpp"
#include "Position.hpp"
#include "ServerGame.hpp"
#include "GameHelper.hpp"
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
    sf::Clock clock;

    _world.manageSystems();
    clock.start();
    while (true) {
        if (clock.getElapsedTime().asMilliseconds() > 50) {
            // Si le jeu a démarré (4 joueurs connectés), gérer les vagues d'ennemis
            //if (_gameStarted && _waveTimer.getElapsedTime().asSeconds() >= 20.f) {
            //    createWave();
            //    _waveTimer.restart();
            //}
            _world.manageSystems();
            clock.restart();
        }
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
    player->addComponent<BoxCollider>(10.f, 10.f);
    player->addComponent<Tag>("player");
    Packet packet;
    packet.positionSpawn(player->getId(), Player, x, y);
    // send all the entity to the client
    _network.sendPacket(packet);
    packet = Packet();
    for (const auto& entity : _world.getAllEntitiesWithComponent<Tag>()) {
        const auto pos = entity->getComponent<Position>();
        const auto tag = entity->getComponent<Tag>();
        entitiesType type = None;
        if (entity->getId() == player->getId())
            continue;
        if (tag->getTag() == "player")
            type = Player;
        else if (tag->getTag() == "enemy")
            type = Enemy;
        else if (tag->getTag() == "bullet")
            type = Bullet;
        packet.positionSpawn(entity->getId(), type, pos->getX(), pos->getY());
    }
    _network.sendPacket(packet);
}

/**
 * @brief define the movement of an enemy.
 *
 * @param entityId the ID if the entity.
 * @param world the world where all entity are contains.
 * @param network network interface
 */
void ServerGame::EnemyMovement(const int entityId, World &world)
{
    const auto entity = GameHelper::getEntityById(world, entityId);

    if (const auto pos = entity->getComponent<Position>(); pos->getX() > 500) {
        pos->setX(pos->getX() - 10 * world.getDeltaTime());
        Packet packet;
        packet.positionSpawn(entityId, None, pos->getX(), pos->getY());
        _network.sendPacket(packet);
    }
}

/**
 * @brief Creates a Ennemy entity.
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
    enemy->addComponent<BoxCollider>(10.f, 10.f);
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<Script>(
        [this](const int entityId, World& world)
        {
            this->EnemyMovement(entityId, world);
        }
    );
    Packet packet;
    packet.positionSpawn(enemy->getId(), Enemy, x, y);
    _network.sendPacket(packet);
}

/**
 * @brief Create a wave of enemies
 */
void ServerGame::createWave()
{
    std::cout << "Spawning enemy wave!" << std::endl;
    for (int i = 0; i < 10; i++)
        createEnemy(1920 + static_cast<float>(i) * 100, 200 + static_cast<float>(i % 3) * 250);
}

/**
 * @brief define the movement of a bullet.
 *
 * @param entityId the ID if the entity.
 * @param world the world where all entity are contains.
 */
void ServerGame::BulletMovement(const int entityId, World &world)
{
    const auto entity = GameHelper::getEntityById(world, entityId);
    const auto pos = entity->getComponent<Position>();
    Packet packet;

    if (entity->getComponent<BoxCollider>()->isTrigger()) {
        // check collisions with enemies
    }
    if (pos->getX() > 3000) {
        world.killEntity(entityId);
        packet.dead(entityId);
    } else {
        pos->setX(pos->getX() + 10 * world.getDeltaTime());
        packet.positionSpawn(entityId, None, pos->getX(), pos->getY());
    }
    _network.sendPacket(packet);
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
    bullet->addComponent<BoxCollider>(5.f, 5.f);
    bullet->addComponent<Tag>("bullet");
    bullet->addComponent<Script>(
        [this](const int entityId, World& world)
        {
            this->BulletMovement(entityId, world);
        }
    );
    Packet packet;
    packet.positionSpawn(bullet->getId(), Bullet, x, y);

    _network.sendPacket(packet);
}

/**
 * @brief Create a new player when a client connect.
 */
void ServerGame::handleNewPlayer()
{
    if (_playerCount >= MAX_PLAYER) {
        std::cout << "Maximum number of players reached (" << MAX_PLAYER << ")" << std::endl;
        return;
    }
    
    createPlayer(200, 200);
    _playerCount++;
    
    std::cout << "Player " << _playerCount << " connected" << std::endl;
    
    if (_playerCount == NB_PLAYER_TO_START && !_gameStarted) {
        _gameStarted = true;
        _waveTimer.restart();
        std::cout << "Game started! Enemy waves will spawn every 20 seconds" << std::endl;
    }
}

/**
 * @brief check if the new position send by the client is valid and change it in server side.
 *
 * @param id The id of the player who is moving.
 * @param x The new x position of the player.
 * @param y The new y position of the player.
 */
void ServerGame::handleNewPlayerPosition(const int id, const float x, const float y)
{
    const auto entity = GameHelper::getEntityById(_world, id);

    if (entity == nullptr) {
        std::cerr << "[Warning] Ignore position update for unknown entity ID: " << id << std::endl;
        return; 
    }

    const auto pos = entity->getComponent<Position>();

    const auto distanceX = pos->getX() - x;
    const auto distanceY = pos->getY() - y;

    if (distanceX * distanceX + distanceY * distanceY <= 20.f) {
        pos->setX(x);
        pos->setY(y);
    }

    Packet packet;
    packet.playerPosition(id, x, y);
    _network.sendPacket(packet);
}

/**
 * @brief Create a bullet at the place of the player who is shooting.
 *
 * @param id The id of the player who is shooting.
 */
void ServerGame::handleShoot(const int id)
{
    const auto entity = GameHelper::getEntityById(_world, id);
    const auto pos = entity->getComponent<Position>();
    createBullet(pos->getX(), pos->getY());
}
