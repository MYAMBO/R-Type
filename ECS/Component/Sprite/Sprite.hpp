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

#include "Component.hpp"

/**
 * @brief Sprite component to handle graphical representation of an entity.
 *
 * This component encapsulates an SFML sprite and its associated texture.
 * It provides methods to retrieve and modify the sprite.
*/
class Sprite : public Component {
    public:
        explicit Sprite(const std::string& filepath);
        ~Sprite() override = default;

        [[nodiscard]] std::shared_ptr<sf::Sprite> getSprite() const;

        void setSprite(const std::shared_ptr<sf::Sprite>& sprite);
    private:
        sf::Texture _texture;
        std::shared_ptr<sf::Sprite> _sprite;
};

#endif /* !SPRITE_HPP_ */