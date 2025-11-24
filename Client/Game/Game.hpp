/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include <SFML/Graphics.hpp>

class Game {
    public:
        Game();
        ~Game();

        void run();
    private:
        sf::RenderWindow _window;
};

#endif