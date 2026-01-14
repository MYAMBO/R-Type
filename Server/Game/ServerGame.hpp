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
        void handleNewPlayerPosition(int id, float x, float y);
        void handleShoot(int id);
        void handleNewPlayer();
        void startLevel(int levelId);
        void createEnemy(float x, float y);
        void createSinusEnemy(float x, float y);
        void createShootingEnemy(float x, float y);
        void createSinusShootingEnemy(const float x, const float y);

    private:
        void createPlayer(float x, float y);
        void createWave();
        void createBullet(float x, float y);
        void createEnemyBullet(float x, float y);
        void EnemyMovement(int entityId, World &world);
        void EnemySinusMovement(int entityId, World &world);
        void ShootingAction(int entityId, World &world);
        void BulletMovement(int entityId, World &world);
        void checkDeaths();


        World _world;
        IGameNetwork& _network;
        int _playerCount = 0;
        bool _gameStarted = false;
        sf::Clock _waveTimer;
};

#endif //R_TYPE_GAME_H