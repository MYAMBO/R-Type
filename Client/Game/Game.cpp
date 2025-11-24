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

#include "../../ECS/Entity/Component/HP/HP.hpp"
#include "../../ECS/Entity/Entity.hpp"
#include "../../ECS/Entity/Component/Position/Position.hpp"
#include "../../ECS/Entity/Component/Sprite/Sprite.hpp"
#include "../../ECS/World.hpp"


Game::Game() : _window(sf::VideoMode({800, 600}), "R-Type Game")
{
}

Game::~Game()
{
}


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