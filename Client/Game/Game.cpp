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

#include "HP.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "Layer.hpp"
#include "Sprite.hpp"
#include "Position.hpp"
#include "Updater.hpp"
#include "Velocity.hpp"
#include "BoxCollider.hpp"
#include "Animator.hpp"
#include "Updater.hpp"
#include "Inputs.hpp"
#include "Draw.hpp"

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
    auto player = world.createEntity();
    player->addComponent<HP>(100);
    player->addComponent<Position>(0.0f, 0.0f);
    player->addComponent<Sprite>(std::string("../sprites/r-typesheet11.gif"));
    player->addComponent<Animator>(3, 0.2f, 0, 0, 33, 33, 33, 0);
    auto pos = player->getComponent<Position>();
    if (pos)
        std::cout << "Player position: (" << pos->getX() << ", " << pos->getY() << ")\n";
    sf::VideoMode videoMode(sf::Vector2u(1920, 1080));
    sf::RenderWindow window(videoMode, "My Window");
    sf::Clock clock;
    world.addSystem<Draw>();
    world.addSystem<Inputs>();
    world.addSystem<Updater>();
    auto inputSystem = world.getSystem<Inputs>();
    window.setFramerateLimit(30); 
    world.setWindow(window);
    while (window.isOpen()) {

        float dt = clock.restart().asSeconds();
        updater.update(dt, world);

        window.clear(sf::Color::Black);
        while (const std::optional eventOpt = window.pollEvent()) {
            world.setEvent(*eventOpt);
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Escape))
                window.close();
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Right))
                pos->setX(pos->getX() + 1.0f);
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Left))
                pos->setX(pos->getX() - 1.0f);
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Up))
                pos->setY(pos->getY() - 1.0f);
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Down))
                pos->setY(pos->getY() + 1.0f);
            if (const auto* keyEvent = eventOpt->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::P) {
                    window.close();
                }
            }
            if (eventOpt->is<sf::Event::Closed>())
                window.close();
        }
        world.manageSystems();
        window.display();
    }
}