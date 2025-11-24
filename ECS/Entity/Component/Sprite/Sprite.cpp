/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Sprite
*/

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Sprite.hpp"

Sprite::Sprite(const std::string& filepath)
{
    if (!_texture.loadFromFile(filepath))
        throw std::runtime_error("Failed to load texture from file: " + filepath);
    
    _sprite = std::make_shared<sf::Sprite>(_texture);
}

std::shared_ptr<sf::Sprite> Sprite::getSprite() const
{
    return _sprite;
}