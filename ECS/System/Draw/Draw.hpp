/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Draw
*/

#pragma once

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
