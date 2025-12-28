/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Mouse
*/

#include "Mouse.hpp"

#include "Scene.hpp"
#include "Button.hpp"
#include "Sprite.hpp"
#include "Position.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

void Mouse::update(const float& dt, World &world)
{
    (void)dt;
    auto window = world.getWindow();
    if (!window)
        return;

    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
    sf::Vector2f mousePos = window->mapPixelToCoords(pixelPos);

    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    for (auto &entity : world.getAllEntitiesWithComponent<Button>()) {
        if (world.getCurrentScene() != entity->getComponent<Scene>()->getScene())
            continue;
        auto button = entity->getComponent<Button>();
        auto pos = entity->getComponent<Position>();
        auto spriteComp = entity->getComponent<Sprite>();

        if (!pos) continue;

        sf::FloatRect bounds({pos->getX(), pos->getY()}, {button->getWidth(), button->getHeight()});

        ButtonState oldState = button->getState();
        ButtonState newState = IDLE;

        if (bounds.contains(mousePos)) {
            if (isMousePressed) {
                newState = PRESSED;
            } else {
                newState = HOVER;
                if (oldState == PRESSED) {
                    button->click();
                } else if (oldState != HOVER) {
                    button->hover();
                }
            }
        } else {
            newState = IDLE;
        }
        button->setState(newState);
        if (button->useColorFilter() && spriteComp) {
            sf::Color targetColor = button->getColor(newState);
            spriteComp->getSprite()->setColor(targetColor);
        }
        if (button->hasTextureRects() && spriteComp) {
            spriteComp->getSprite()->setTextureRect(button->getRect(newState));
        }
    }
}