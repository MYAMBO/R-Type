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
#include "Draw.hpp"
#include "World.hpp"
#include "Layer.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"
#include "Entity.hpp"
#include "Inputs.hpp"
#include "Updater.hpp"
#include "Updater.hpp"
#include "Velocity.hpp"
#include "Position.hpp"
#include "Animator.hpp"
#include "Updater.hpp"
#include "Inputs.hpp"
#include "Draw.hpp"
#include "Scale.hpp"
#include "Tag.hpp"
#include "BoxCollider.hpp"

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
    player->addComponent<Animator>(3, 0.5f, 0, 0, 33, 33, 33, 0);
    player->addComponent<Scale>(10.f);
    player->addComponent<Scene>(1);
    auto pos = player->getComponent<Position>();
    sf::VideoMode videoMode(sf::Vector2u(1920, 1080));
    sf::RenderWindow window(videoMode, "My Window");
    sf::Clock clock;
    world.addSystem<Draw>();
    world.addSystem<Inputs>();
    world.addSystem<Updater>();
    auto inputSystem = world.getSystem<Inputs>();
    window.setFramerateLimit(30); 
    world.setWindow(window);
    world.setCurrentScene(1);
    while (window.isOpen()) {
       float dt = clock.restart().asSeconds();
       world.setDeltaTime(dt);
        window.clear(sf::Color::Black);
        while (const std::optional eventOpt = window.pollEvent()) {
            world.setEvent(*eventOpt);
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Escape, *eventOpt)) {
                printf("Escape key pressed, closing window.\n");
                window.close();
            }
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Right, *eventOpt)) {
                printf("Right key pressed.\n");
                pos->setX(pos->getX() + 1.0f);
            }
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Left, *eventOpt)) {
                printf("Left key pressed.\n");
                pos->setX(pos->getX() - 1.0f);
            }
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Up, *eventOpt)) {
                printf("Up key pressed.\n");
                pos->setY(pos->getY() - 1.0f);
            }
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Down, *eventOpt)) {
                printf("Down key pressed.\n");
                pos->setY(pos->getY() + 1.0f);
            }
            if (const auto* keyEvent = eventOpt->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::P) {
                    window.close();
                }
            }
            if (eventOpt->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        world.manageSystems();
        window.display();
    }
}