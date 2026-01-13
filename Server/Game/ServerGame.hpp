/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#ifndef R_TYPE_GAME_H
    #define R_TYPE_GAME_H

#include <SFML/System.hpp>
#include "IGameNetwork.hpp"
#include "World.hpp"
#include "EntitiesType.hpp"

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
        ServerGame(IGameNetwork& network);
        ~ServerGame() = default;

        void run();
        void serverUpdatePosition(uint32_t id, float x, float y);
        void handleShoot(uint32_t id);
        void handleAction(uint32_t id, uint8_t action, uint32_t data);
        void handleNewPlayer();
        void startLevel(int levelId);
        void createEnemy(float x, float y);
        void createSinusEnemy(float x, float y);
        // void createShootingEnemy(float x, float y);
        // void createSinusShootingEnemy(const float x, const float y);

    private:
        void createPlayer(float x, float y);
        void createWave();
        void createBullet(float x, float y);
        void EnemyMovement(uint32_t entityId, World &world);
        void BulletMovement(uint32_t entityId, World &world);
        void EnemySinusMovement(uint32_t entityId, World &world);
        void checkDeaths();


        World _world;
        IGameNetwork& _network;
        int _playerCount = 0;
        bool _gameStarted = false;
        sf::Clock _waveTimer;
};

#endif //R_TYPE_GAME_H