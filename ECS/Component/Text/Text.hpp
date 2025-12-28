/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Text
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_

#include "Component.hpp"

#include <memory>
#include <string>
#include <iostream>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class Text : public Component {
    public:
        Text(const std::string& content, const std::string& fontPath, unsigned int size = 20);
        ~Text() override = default;

        void setString(const std::string& str);
        void setSize(unsigned int size);
        void setColor(const sf::Color& color);
        
        sf::Text& getSfText();
        std::string getText();
        sf::FloatRect getGlobalBounds() const;

    private:
        std::shared_ptr<sf::Font> _font; 
        std::unique_ptr<sf::Text> _text;
};

#endif /* !TEXT_HPP_ */