/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
    #define SPRITE_HPP_

#include <memory>
#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../Component.hpp"

class Sprite : public Component {
    public:
        Sprite(const std::string& filepath);
        virtual ~Sprite() = default;

        [[nodiscard]] std::shared_ptr<sf::Sprite> getSprite() const;

        void setSprite(const std::shared_ptr<sf::Sprite>& sprite);
    private:
        sf::Texture _texture;
        std::shared_ptr<sf::Sprite> _sprite;
};

#endif /* !SPRITE_HPP_ */