/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#ifndef R_TYPE_GAME_H
    #define R_TYPE_GAME_H

    #include "World.hpp"

class ServerGame {
    public:
        ServerGame();
        ~ServerGame() = default;

        void run();

    private:
        void createPlayer();
        void createEnemy();

        World _world;
};

#endif //R_TYPE_GAME_H