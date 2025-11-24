/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Sprite
*/

#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Component.hpp"

class Sprite : public Component {
    public:
        Sprite(const std::string& filepath);
        virtual ~Sprite() = default;

        std::shared_ptr<sf::Sprite> getSprite() const;

    private:
        sf::Texture _texture;
        std::shared_ptr<sf::Sprite> _sprite;
};
