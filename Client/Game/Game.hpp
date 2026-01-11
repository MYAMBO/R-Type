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
    #include "EntitiesType.hpp"

/**
 * @brief Enumeration for different rendering layers in the game.
 * Each layer is assigned an integer value to determine its rendering order.
*/
enum LayerType {
    BACKGROUND = -1,
    UI = 1000,
};

enum class SceneType {
    LOADING = 0,
    GAMEPLAY = 1,
    MENU = 2,
    OPTIONS = 3,
    MYAMBO = 10,
    KAYU = 11,
    CREDITS = 42,
    PAUSE = 1000,
};

enum PlayerColor {
    BLUE = 0,
    PURPLE,
    RED,
    GREEN
};

// enum entitiesType
// {
//     None = 0,
//     Player = 1,
//     Enemy,
//     Bullet
// };

/**
 * @brief Main Game class to handle the game window and loop.
 */
class Game {
    public:
        Game(IGameNetwork& network, unsigned int width = 1920, unsigned int height = 1080, const std::string& title = "Game");
        ~Game();

        void run();
        void loadingRun();
        int killEntity(int id);
        void handleSpawn(int id, int type, float x, float y);

        void menudisplay();
        void gameplaydisplay();
    private:
        void gameInput(std::shared_ptr<Inputs> inputSystem);

        void playerInput(int entityId, World &world);
        void updateLoadingState(float progress, const std::string& status);
        void smootherMovement(int entityId, World &world, float targetX, float targetY); 
        

        void bulletShooting();

        sf::RenderWindow _window;
        World _world;
        IGameNetwork& _network;
        Creator _creator;

        bool _isShootKeyPressed = false;
        int _musicVolume = 100;
        int _sfxVolume = 100;
};

#endif