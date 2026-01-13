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
    #include "Creator.hpp"
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
        Game(IGameNetwork& network, unsigned int width = 1920, unsigned int height = 1080, const std::string& title = "Game");
        ~Game();

        void run();
        void handleSpawn(uint32_t id, uint16_t type, float x, float y);
        void handleAction(uint32_t id, uint8_t action, uint32_t data);

        int killEntity(int id);
        void menudisplay();
        void gameplaydisplay();

    private:
        void gameInput(std::shared_ptr<Inputs> inputSystem);

        void createCamera();
        void createBackground();
        void createPlayer(uint32_t id = 0);
        void createEnemy(float x, float y, uint16_t type);
        void playerInput(uint32_t entityId, World &world);
        void playerInput(int entityId, World &world);
        void updateLoadingState(float progress, const std::string& status);
        void smootherMovement(int entityId, World &world, float targetX, float targetY);


        void bulletShooting(); // Need to remove it, maybe
        void healEntity(uint32_t entityId, uint32_t amount);

        sf::RenderWindow _window;
        World _world;
        IGameNetwork& _network;
        Creator _creator;

        bool _isShootKeyPressed = false;
};

#endif