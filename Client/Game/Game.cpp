/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** main of the game
*/

#include "Game.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Component/HP/HP.hpp"
#include "../../ECS/World.hpp"
#include "../../ECS/Entity/Entity.hpp"
#include "../../ECS/Component/Layer/Layer.hpp"
#include "../../ECS/Component/Sprite/Sprite.hpp"
#include "../../ECS/Component/Position/Position.hpp"
#include "../../ECS/Component/BoxCollider/BoxCollider.hpp"

/**
 * @brief Constructs a new Game object.
 *
 * Initializes the game window with specified dimensions and title.
 * @param width The width of the game window in pixels. Default is 800.
 * @param height The height of the game window in pixels. Default is 600.
 * @param title The title of the game window. Default is "Game".
 */
Game::Game(unsigned int width, unsigned int height, const std::string& title)
    : _window(sf::VideoMode({width, height}), title)
{
}

/**
 * @brief Destroys the Game object.
 */
Game::~Game()
{
    _window.close();
}

/**
 * @brief Runs the main game loop.
 *
 * This function initializes the game world, creates entities,
 * and handles the main event loop for rendering and user input.
 */
void Game::run()
{
    World world;
    Entity player;

    player.addComponent<HP>(100);
    player.addComponent<Position>(0.0f, 0.0f);
    player.addComponent<Sprite>(std::string("../sprite/YaeMiko.jpg"));

    auto pos = player.getComponent<Position>();
    if (pos)
        std::cout << "Player position: (" << pos->getX() << ", " << pos->getY() << ")\n";

    sf::VideoMode videoMode(sf::Vector2u(1920, 1080));
    sf::RenderWindow window(videoMode, "My Window");

    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        auto sprite = player.getComponent<Sprite>();
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                auto pos = player.getComponent<Position>();
                if (pos) {
                    switch (keyPressed->scancode) {
                        case sf::Keyboard::Scancode::Up:
                            pos->setY(pos->getY() - 10.0f);
                            break;
                        case sf::Keyboard::Scancode::Down:
                            pos->setY(pos->getY() + 10.0f);
                            break;
                        case sf::Keyboard::Scancode::Left:
                            pos->setX(pos->getX() - 10.0f);
                            break;
                        case sf::Keyboard::Scancode::Right:
                            pos->setX(pos->getX() + 10.0f);
                            break;
                        default:
                            break;
                    }
                    sprite->getSprite()->setPosition(sf::Vector2f(pos->getX(), pos->getY()));
                }
            }
        }
        if (sprite) {
            window.draw(*sprite->getSprite());
        }
        window.display();
    }
}