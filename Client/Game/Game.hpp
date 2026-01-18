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
    #include "Factory.hpp"
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
    LANGUAGES = 4,
    WAITING_ROOM = 5,
    MYAMBO = 10,
    KAYU = 11,
    CREDITS = 42,
    PAUSE = 1000,
    GAME_OVER = 8,
    VICTORY = 9,
};

enum PlayerColor {
    BLUE = 0,
    PURPLE,
    RED,
    GREEN
};

/**
 * @brief Main Game class to handle the game window and loop.
 */
class Game {
    public:
        Game(IGameNetwork& network, unsigned int width = 1920, unsigned int height = 1080, const std::string& title = "Game");
        ~Game();

        void run();
        void updateEntity(uint32_t id, uint16_t type, float x, float y);
        void handleAction(uint32_t id, uint8_t action, uint32_t data);

        void loadingRun();
        int killEntity(int id);
        void menudisplay();
        void gameplaydisplay();
        void showEndScreen(uint8_t status);
        void createEnemy(float x, float y, uint16_t type);
        void updatePlayerMana(uint32_t playerId, int mana);
        void startGameFromServer();

    private:
        void gameInput(std::shared_ptr<Inputs> inputSystem);

        void savefile();
        void loadfile();
        void playerInput(uint32_t entityId, World &world);
        void updateLoadingState(float progress, const std::string& status);
        void smootherMovement(int entityId, World &world, float targetX, float targetY);


        void bulletShooting(); // Need to remove it, maybe
        void healEntity(uint32_t entityId, uint32_t amount);

        sf::RenderWindow _window;
        World _world;
        IGameNetwork& _network;
        Factory _factory;
        Packet _packet;

        bool _isShootKeyPressed = false;
            bool _startGameRequested = false;
        int _musicVolume = 100;
        int _sfxVolume = 100;
};

#endif