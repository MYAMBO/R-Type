/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include <SFML/Graphics.hpp>

    #include "World.hpp"
    #include "Inputs.hpp"
    #include "IGameNetwork.hpp"

/**
 * @brief Enumeration for different rendering layers in the game.
 * Each layer is assigned an integer value to determine its rendering order.
*/
enum LayerType {
    BACKGROUND = -1,
    UI = 1000,
};

enum PlayerColor {
    BLUE = 0,
    PURPLE,
    RED,
    GREEN
};

enum entitiesType
{
    None = 0,
    Player = 1,
    Enemy,
    Bullet
};

/**
 * @brief Main Game class to handle the game window and loop.
 */
class Game {
    public:
        Game(IGameNetwork& network, unsigned int width = 800, unsigned int height = 600, const std::string& title = "Game");
        ~Game();

        void run();
        void handleSpawn(int id, int type, float x, float y);
    private:
        void gameInput(std::shared_ptr<Inputs> inputSystem);

        void createCamera();
        void createPlayer();
        void createBackground();
        void createEnemy(float x, float y, int type);
        void playerInput(int entityId, World &world);

        void bulletShooting();

        World _world;
        sf::RenderWindow _window;
        IGameNetwork& _network;
        bool _isShootKeyPressed = false;
};

#endif