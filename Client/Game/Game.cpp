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
#include "Camera.hpp"
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
    createPlayer();
    _world.addSystem<Updater>();
    _world.addSystem<Draw>();
    _world.addSystem<Inputs>();
    _window.setFramerateLimit(30); 
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
    sf::Clock clock;
    auto inputSystem = _world.getSystem<Inputs>();
    _world.setWindow(_window);
    _world.setCurrentScene(1);
    while (_window.isOpen()) {
        _window.clear(sf::Color::Black);
        float dt = clock.restart().asSeconds();
        _world.setDeltaTime(dt);
        gameInput(inputSystem);
        laserMovement();
        _world.manageSystems();
        _window.display();
    }
}

/**
 * @brief Handles game input.
 *
 * This function processes user input events and updates the game state accordingly.
 * @param inputSystem The input system to check for player actions.
 */
void Game::gameInput(std::shared_ptr<Inputs> inputSystem)
{
    while (const std::optional eventOpt = _window.pollEvent()) {
        _world.setEvent(*eventOpt);
        if (const auto* keyEvent = eventOpt->getIf<sf::Event::KeyPressed>()) {
            if (keyEvent->code == sf::Keyboard::Key::P)
                _window.close();
        }
        if (eventOpt->is<sf::Event::Closed>()) {
            _window.close();
        }
        inputSystem->update(0.0f, _world);
    }
    playerInput(inputSystem);
}

/**
 * @brief Handles player input.
 *
 * This function processes user input events and updates the game state accordingly.
 * @param inputSystem The input system to check for player actions.
 */
void Game::playerInput(std::shared_ptr<Inputs> inputSystem)
{
    for (auto& player : _world.getAllEntitiesWithComponent<Tag>()) {
        auto tagComp = player->getComponent<Tag>();
        if (tagComp && tagComp->getTag() == "player") {
            auto pos = player->getComponent<Position>();
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Escape))
                _window.close();
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Right))
                pos->setX(pos->getX() + 7.0f);
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Left))
                pos->setX(pos->getX() - 7.0f);
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Up))
                pos->setY(pos->getY() - 7.0f);
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Down))
                pos->setY(pos->getY() + 7.0f);
            if (inputSystem->isKeyPressed(KeyboardKey::Key_E))
                createLaser(player->getId());
            for (auto& fire : _world.getAllEntitiesWithComponent<Tag>()) {
                auto tagCompFire = fire->getComponent<Tag>();
                if (tagCompFire && tagCompFire->getTag() == "fire") {
                    auto posPlayer = player->getComponent<Position>();
                    auto posFire = fire->getComponent<Position>();
                    if (posPlayer && posFire) {
                        posFire->setX(posPlayer->getX() - 25.f);
                        posFire->setY(posPlayer->getY() + 10.f);
                    }
                }
            }
        }
    }
}

/**
 * @brief Creates the player entity.
 * 
 * This function initializes the player entity with necessary components.
 */
void Game::createPlayer()
{
    auto player = _world.createEntity();
    player->addComponent<HP>(100);
    player->addComponent<Position>(75.0f, 75.0f);
    player->addComponent<Sprite>(std::string("../sprites/r-typesheet42.gif"));
    player->addComponent<Animator>(2, 0.1f, 0, 0, 33, 19, 33, 0);
    player->addComponent<Scale>(2.f);
    player->addComponent<Scene>(1);
    player->addComponent<Camera>(sf::Vector2f(1920.f, 1080.f), sf::Vector2f(player->getComponent<Position>()->getX(), player->getComponent<Position>()->getY()));
    player->addComponent<Tag>("player");
    auto fire = _world.createEntity();
    fire->addComponent<Position>(0.f, 85.f);
    fire->addComponent<Sprite>(std::string("../sprites/r-typesheet1.gif"));
    fire->addComponent<Animator>(2, 0.1f, 285, 85, 15, 15, 20, 0);
    fire->addComponent<Scale>(2.f);
    fire->addComponent<Scene>(1);
    fire->addComponent<Tag>("fire");
}

/**
 * @brief Creates a laser entity.
 *
 * This function initializes a laser entity with necessary components.
 * @param entityId The ID of the entity that fired the laser.
 */
void Game::createLaser(int entityId)
{
    auto laser = _world.createEntity();
    auto shooter = _world.getAllEntitiesWithComponent<Tag>()[entityId];
    auto shooterPos = shooter->getComponent<Position>();
    laser->addComponent<Position>(shooterPos->getX() + 60.f, shooterPos->getY() + 15.f);
    laser->addComponent<Sprite>(std::string("../sprites/r-typesheet1.gif"));
    laser->addComponent<Animator>(2, 0.05f, 200, 120, 32, 15, 32, 0);
    laser->addComponent<Scale>(2.f);
    laser->addComponent<Scene>(1);
    laser->addComponent<Tag>("laser");
}

/**
 * @brief handles laser movement.
 * This function updates the position of all laser entities.
 */
void Game::laserMovement()
{
    for (auto& laser : _world.getAllEntitiesWithComponent<Tag>()) {
        auto tagComp = laser->getComponent<Tag>();
        if (tagComp && tagComp->getTag() == "laser") {
            auto pos = laser->getComponent<Position>();
            pos->setX(pos->getX() + 10.0f);
            if (pos->getX() > 1920.f) {
                _world.killEntity(laser->getId());
            }
        }
    }
}