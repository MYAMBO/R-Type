/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Draw
*/

#ifndef DRAW_HPP_
    #define DRAW_HPP_

#include <SFML/Graphics/RenderWindow.hpp>

#include "World.hpp"

/**
 * @brief Draw system responsible for rendering entities with Sprite components.
 *
 * This system iterates through all entities in the world that have a Sprite component
 * and draws them to the render window.
*/
class Draw : public System {
    public:
        Draw();
        virtual ~Draw() = default;

        virtual void update(const float& dt, World &w);

    private:
        sf::RenderWindow _window;
};

#endif