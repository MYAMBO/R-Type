/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#ifndef R_TYPE_GAME_H
    #define R_TYPE_GAME_H

#include <unordered_set>
#include <memory>
#include <string>
#include <SFML/System.hpp>
#include "IGameNetwork.hpp"
#include "World.hpp"
#include "EntitiesType.hpp"
#include "LevelLoader.hpp"
#include "User.hpp"

#define NB_PLAYER_TO_START 2
    #define MAX_PLAYER 4

// enum entitiesType
// {
//     None = 0,
//     Player = 1,
//     Enemy = 2,
//     Bullet = 3
// };

class ServerGame {
    public:
        ServerGame(IGameNetwork& network, uint32_t &tick, std::vector<std::pair<Packet, uint32_t>> &ackPackets, std::vector<User> &users);
        ~ServerGame() = default;

        void run();
        void serverUpdatePosition(uint32_t id, float x, float y);
        void handleShoot(uint32_t id);
        void handleHeal(uint32_t id);
        void handleAction(uint32_t id, uint8_t action, uint32_t data);
        void handleNewPlayer();
        void handlePlayerReady(uint32_t playerId);
        void createEnemy(float x, float y);
        void createFast(float x, float y);
        void createTank(float x, float y);
        void createSinusEnemy(float x, float y);
        void createShootingEnemy(float x, float y);
        void createSinusShootingEnemy(const float x, const float y);
        void createPortalBoss(const float x, const float y);
        void createHealPowerUp(const float x, const float y);
        void createWarningPortal(const float x, const float y, float duration);
        void checkGameEnd();
        void sendGameEnd(uint8_t status);


    private:
        void createPlayer(float x, float y);
        void createWave();
        void createBullet(float x, float y);
        void createEnemyBullet(float x, float y);
        void createEnemyBackwardBullet(float x, float y);
        void EnemyMovement(uint32_t  entityId, World &world);
        void EnemySinusMovement(uint32_t  entityId, World &world);
        void ShootingAction(int entityId, World &world);
        void BulletMovement(uint32_t  entityId, World &world);
        void checkDeaths();
        void manaRegenScript(int entityId, World &world);
        void portalBossBarrageScript(int entityId, World& world);
        void portalBossBackwardPortalScript(int entityId, World& world);
        void portalBossSpawnTankScript(int entityId, World& world);
        bool resolveBulletSpawnOverlap(const std::shared_ptr<Entity>& bullet, const std::string& targetTag);

        uint32_t& _tick;
        World _world;
        Packet _packet;
        IGameNetwork& _network;
        LevelLoader _levelLoader;
        int _playerCount = 0;
        int _readyCount = 0;
        bool _gameStarted = false;
        sf::Clock _waveTimer;
        std::unordered_set<uint32_t> _readyPlayers;
        std::vector<std::pair<Packet, uint32_t>> _ackPackets;
        std::vector<User> _users;
};

#endif //R_TYPE_GAME_H