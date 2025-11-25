/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Sprite
*/

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Sprite.hpp"

/**
 * @brief Constructs a new Sprite component by loading a texture from the specified file path.
 *
 * @param filepath The path to the image file to load as a texture.
 * @throws std::runtime_error if the texture fails to load.
 */
Sprite::Sprite(const std::string& filepath)
{
    if (!_texture.loadFromFile(filepath))
        throw std::runtime_error("Failed to load texture from file: " + filepath);
    
    _sprite = std::make_shared<sf::Sprite>(_texture);
}

/**
 * @brief Gets the sprite associated with this component.
 *
 * @return A shared pointer to the SFML sprite.
 */
std::shared_ptr<sf::Sprite> Sprite::getSprite() const
{
    return _sprite;
}

/**
 * @brief Sets the sprite associated with this component.
 *
 * @param sprite A shared pointer to the new SFML sprite.
 */
void Sprite::setSprite(const std::shared_ptr<sf::Sprite>& sprite)
{
    _sprite = sprite;
}