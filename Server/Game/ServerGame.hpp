/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#ifndef R_TYPE_GAME_H
    #define R_TYPE_GAME_H

    #include "World.hpp"

    #define NB_PLAYER 4

enum entitiesType
{
    None = 0,
    Player = 1,
    Enemy,
    Bullet
};

class ServerGame {
    public:
        ServerGame();
        ~ServerGame() = default;

        void run();
        void handleNewPlayerPosition(int id, float x, float y) const;
        void handleShoot(int id);
        void handleNewPlayer();

    private:
        void createPlayer(float x, float y);
        void createEnemy(float x, float y);
        void createWave();
        void createBullet(float x, float y);

        World _world;
};

#endif //R_TYPE_GAME_H