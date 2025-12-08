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

/**
 * @brief Enumeration for different rendering layers in the game.
 * Each layer is assigned an integer value to determine its rendering order.
*/
enum LayerType {
    BACKGROUND = -1,
    UI = 1000,
};

/**
 * @brief Main Game class to handle the game window and loop.
 */
class Game {
    public:
        Game(unsigned int width = 800, unsigned int height = 600, const std::string& title = "Game");
        ~Game();

        void run();
    private:
        void gameInput(std::shared_ptr<Inputs> inputSystem);
        void playerInput(std::shared_ptr<Inputs> inputSystem, sf::Event eventOpt);

        World _world;
        sf::RenderWindow _window;
};

#endif