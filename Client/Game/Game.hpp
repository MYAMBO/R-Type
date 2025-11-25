/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include <SFML/Graphics.hpp>

enum LayerType {
    BACKGROUND = -1,
    UI = 1000,
};

class Game {
    public:
        Game(unsigned int width = 800, unsigned int height = 600, const std::string& title = "Game");
        ~Game();

        void run();
    private:
        sf::RenderWindow _window;
};

#endif