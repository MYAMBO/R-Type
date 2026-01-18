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

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class Text : public Component {
    public:
        Text(const std::string& content, const std::string& fontPath, unsigned int size = 20);
        ~Text() override = default;

        void setString(const std::string& str);
        void setSize(unsigned int size);
        void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
        void setFont(const std::string& fontPath);
        
        sf::Text& getSfText();
        std::string getText();
        unsigned int getSize() const;
        sf::FloatRect getGlobalBounds() const;
        std::string getFontPath() const;

    private:
        std::shared_ptr<sf::Font> _font; 
        std::unique_ptr<sf::Text> _text;
        std::string _fontPath;
};

#endif /* !TEXT_HPP_ */