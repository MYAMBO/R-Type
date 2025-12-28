/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Button Component
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_

#include "Component.hpp"
#include <functional>
#include <SFML/Graphics/Rect.hpp>

enum ButtonState {
    IDLE = 0,
    HOVER,
    PRESSED
};

class Button : public Component {
    public:
        Button(float width, float height);
        ~Button() override = default;

        [[nodiscard]] float getWidth() const;
        [[nodiscard]] float getHeight() const;
        [[nodiscard]] ButtonState getState() const;

        void setState(ButtonState state);
        void setOnClick(std::function<void()> callback);
        void setOnHover(std::function<void()> callback);

        void click();
        void hover();

        void setTextureRects(const sf::IntRect& idle, const sf::IntRect& hover, const sf::IntRect& pressed);
        [[nodiscard]] bool hasTextureRects() const;
        [[nodiscard]] const sf::IntRect& getRect(ButtonState s) const;
    private:
        float _width;
        float _height;
        ButtonState _state;

        std::function<void()> _onClick;
        std::function<void()> _onHover;

        bool _hasTextureRects = false;
        sf::IntRect _rectIdle;
        sf::IntRect _rectHover;
        sf::IntRect _rectPressed;
};

#endif /* !BUTTON_HPP_ */