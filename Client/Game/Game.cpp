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
#include "Layer.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"
#include "Entity.hpp"
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
    auto player = _world.createEntity();
    player->addComponent<HP>(100);
    player->addComponent<Position>(0.0f, 0.0f);
    player->addComponent<Sprite>(std::string("../sprites/r-typesheet11.gif"));
    player->addComponent<Animator>(3, 0.5f, 0, 0, 33, 33, 33, 0);
    player->addComponent<Scale>(10.f);
    player->addComponent<Scene>(1);
    sf::VideoMode videoMode(sf::Vector2u(1920, 1080));
    sf::Clock clock;
    _world.addSystem<Draw>();
    _world.addSystem<Inputs>();
    _world.addSystem<Updater>();
    auto inputSystem = _world.getSystem<Inputs>();
    _window.setFramerateLimit(30); 
    _world.setWindow(_window);
    _world.setCurrentScene(1);
    while (_window.isOpen()) {
        float dt = clock.restart().asSeconds();
        _world.setDeltaTime(dt);
        gameInput(inputSystem);
        _window.clear(sf::Color::Black);
        _world.manageSystems();
        _window.display();
    }
}

void Game::gameInput(std::shared_ptr<Inputs> inputSystem)
{
    while (const std::optional eventOpt = _window.pollEvent()) {
        _world.setEvent(*eventOpt);
        if (const auto* keyEvent = eventOpt->getIf<sf::Event::KeyPressed>()) {
            if (keyEvent->code == sf::Keyboard::Key::P) {
                _window.close();
            }
        }
        if (eventOpt->is<sf::Event::Closed>()) {
            _window.close();
        }
        playerInput(inputSystem, *eventOpt);
    }
}


/**
 * @brief Handles player input.
 *
 * This function processes user input events and updates the game state accordingly.
 */
void Game::playerInput(std::shared_ptr<Inputs> inputSystem, sf::Event eventOpt)
{
    auto pos = player->getComponent<Position>();
    if (inputSystem->isKeyPressed(KeyboardKey::Key_Escape, eventOpt))
        _window.close();
    if (inputSystem->isKeyPressed(KeyboardKey::Key_Right, eventOpt))
        pos->setX(pos->getX() + 1.0f);
    if (inputSystem->isKeyPressed(KeyboardKey::Key_Left, eventOpt))
        pos->setX(pos->getX() - 1.0f);
    if (inputSystem->isKeyPressed(KeyboardKey::Key_Up, eventOpt))
        pos->setY(pos->getY() - 1.0f);
    if (inputSystem->isKeyPressed(KeyboardKey::Key_Down, eventOpt))
        pos->setY(pos->getY() + 1.0f);
}
