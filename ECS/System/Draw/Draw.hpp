/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Draw
*/

#ifndef DRAW_HPP_
    #define DRAW_HPP_

#include <SFML/Graphics/RenderWindow.hpp>

#include "../../World.hpp"

class Draw : public System{
    public:
        Draw();
        virtual ~Draw() = default;

        virtual void update(const float& dt, World &w);

    private:
        sf::RenderWindow _window;
};

#endif /* !DRAW_HPP_ */