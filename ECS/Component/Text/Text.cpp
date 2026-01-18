/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Text
*/

#include <iostream>

#include "Text.hpp"

/**
* @brief Constructor of the Text component
* @param content The string content of the text
* @param fontPath The path to the font file
* @param size The character size of the text
*/
Text::Text(const std::string& content, const std::string& fontPath, unsigned int size)
    : _fontPath(fontPath)
{
    _font = std::make_shared<sf::Font>();
    if (!_font->openFromFile(fontPath)) {
        std::cerr << "Error: Could not load font " << fontPath << std::endl;
    }   
    _text = std::make_unique<sf::Text>(*_font, content, size);
    _text->setFillColor(sf::Color::White);
}

/**
*   @brief Sets the string content of the text.
*   @param str The new string content
*/
void Text::setString(const std::string& str)
{
    _text->setString(str);
}

/**
*   @brief Sets the character size of the text.
*   @param size The new character size
 */
void Text::setSize(unsigned int size)
{
    _text->setCharacterSize(size);
}

/**
*   @brief Sets the color of the text.
*   @param color The new color 
*/
void Text::setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    sf::Color color(red, green, blue, alpha);
    _text->setFillColor(color);
}

/**
*  @brief Gets the underlying SFML Text object.
*  @return Reference to the SFML Text object
*/
sf::Text& Text::getSfText()
{
    return *_text;
}

/**  @brief Gets the global bounds of the text.
*  @return The global bounds as an SFML FloatRect
*/
sf::FloatRect Text::getGlobalBounds() const
{
    return _text->getGlobalBounds();
}

/** 
*  @brief Gets the string content of the text.
*  @return The string content
*/
std::string Text::getText()
{
    return _text->getString();
}

/**
*  @brief Gets the character size of the text.
*  @return The character size
*/
unsigned int Text::getSize() const
{
    return _text->getCharacterSize();
}

/**
*  @brief Sets the font of the text.
*  @param fontPath The path to the new font file
*/
void Text::setFont(const std::string& fontPath)
{
    if (!_font->openFromFile(fontPath)) {
        std::cerr << "Error: Could not load font " << fontPath << std::endl;
        return;
    }
    _fontPath = fontPath;
    _text->setFont(*_font);
}

std::string Text::getFontPath() const
{
    return _fontPath;
}