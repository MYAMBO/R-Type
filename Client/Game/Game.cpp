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
#include "Script.hpp"
#include "Inputs.hpp"
#include "Draw.hpp"
#include "Scale.hpp"
#include "Tag.hpp"
#include "GameHelper.hpp"
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
    createCamera();
    createEnemy(600.f, 100.f, 1);
    _world.addSystem<Updater>();
    _world.addSystem<Draw>();
    _world.addSystem<Inputs>();
    _window.setFramerateLimit(30); 
    _world.setDeltaTime(1.f);
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
    auto inputSystem = _world.getSystem<Inputs>();
    _world.setWindow(_window);
    _world.setCurrentScene(1);
    while (_window.isOpen()) {
        _window.clear(sf::Color::Black);
        gameInput(inputSystem);
        bulletMovement();
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
        if (const auto* keyEvent = eventOpt->getIf<sf::Event::KeyPressed>())
            if (inputSystem->isKeyPressed(KeyboardKey::Key_Escape))
                _window.close();
        if (eventOpt->is<sf::Event::Closed>())
            _window.close();
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
    std::shared_ptr<Camera> compCam = GameHelper::getMainCamera(_world);
    if (!compCam)
        return;

    std::shared_ptr<Entity> compPlayer = GameHelper::getEntityByTag(_world, "player");
    if (!compPlayer)
        return;

    auto pos = compPlayer->getComponent<Position>();

    if (inputSystem->isKeyPressed(KeyboardKey::Key_D))
        if (compCam->getPosition().x + compCam->getSize().x > pos->getX() + 7.0f)
            pos->setX(pos->getX() + 7.0f);
    if (inputSystem->isKeyPressed(KeyboardKey::Key_Q))
        if (compCam->getPosition().x < pos->getX() - 7.0f)
            pos->setX(pos->getX() - 7.0f);
    if (inputSystem->isKeyPressed(KeyboardKey::Key_Z))
        if (compCam->getPosition().y < pos->getY() - 7.0f)
            pos->setY(pos->getY() - 7.0f);
    if (inputSystem->isKeyPressed(KeyboardKey::Key_S))
        if (compCam->getPosition().y + compCam->getSize().y > pos->getY() + 7.0f)
            pos->setY(pos->getY() + 7.0f);
    if (inputSystem->isKeyPressed(KeyboardKey::Key_Space)) {
        if (!_isShootKeyPressed) {
            createBullet(compPlayer->getId());
            _isShootKeyPressed = true;
        }
    } else {
        _isShootKeyPressed = false;
    }

    for (auto& fire : _world.getAllEntitiesWithComponent<Tag>()) {
        auto tagCompFire = fire->getComponent<Tag>();
        if (tagCompFire && tagCompFire->getTag() == "fire") {
            auto posPlayer = compPlayer->getComponent<Position>();
            auto posFire = fire->getComponent<Position>();
            if (posPlayer && posFire) {
                posFire->setX(posPlayer->getX() - 25.f);
                posFire->setY(posPlayer->getY() + 10.f);
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
    player->addComponent<Animator>(2, 1, 3.f, 0, 0, 33, 19, 0, 0);
    player->addComponent<Scale>(2.f);
    player->addComponent<Scene>(1);
    player->addComponent<Tag>("player");
    auto fire = _world.createEntity();
    fire->addComponent<Position>(0.f, 85.f);
    fire->addComponent<Sprite>(std::string("../sprites/r-typesheet1.gif"));
    fire->addComponent<Animator>(2, 1, 3.f, 285, 85, 15, 15, 0, 0);
    fire->addComponent<Scale>(2.f);
    fire->addComponent<Scene>(1);
    fire->addComponent<Tag>("fire");
}

/**
 * @brief Creates a bullet entity.
 *
 * This function initializes a bullet entity with necessary components.
 * @param entityId The ID of the entity that fired the bullet.
 */
void Game::createBullet(int entityId)
{
    auto bullet = _world.createEntity();
    auto shooter = _world.getAllEntitiesWithComponent<Tag>()[entityId];
    auto shooterPos = shooter->getComponent<Position>();
    bullet->addComponent<Position>(shooterPos->getX() + 60.f, shooterPos->getY() + 15.f);
    bullet->addComponent<Sprite>(std::string("../sprites/r-typesheet1.gif"));
    bullet->addComponent<Animator>(2, 1, 1.5f, 200, 120, 32, 15, 32, 0);
    bullet->addComponent<Scale>(2.f);
    bullet->addComponent<Scene>(1);
    bullet->addComponent<Tag>("bullet");
}

/**
 * @brief handles bullet movement.
 * This function updates the position of all bullet entities.
 */
void Game::bulletMovement()
{
    std::shared_ptr<Camera> compCam = GameHelper::getMainCamera(_world);
    if (!compCam)
        return;
    for (auto& bullet : _world.getAllEntitiesWithComponent<Tag>()) {
        auto tagComp = bullet->getComponent<Tag>();
        if (tagComp && tagComp->getTag() == "bullet") {
            auto pos = bullet->getComponent<Position>();
            pos->setX(pos->getX() + 10.0f);
            if (pos->getX() > compCam->getPosition().x + compCam->getSize().x)
                _world.killEntity(bullet->getId());
        }
    }
}

/**
 * @brief Create Camera
 * This function initializes a camera entity with necessary components.
*/
void Game::createCamera()
{
    auto cameraEntity = _world.createEntity();
    cameraEntity->addComponent<Camera>(sf::Vector2f(1920.f, 1080.f), sf::Vector2f(0.f, 0.f));
    cameraEntity->addComponent<Tag>("main_camera");
}

/**
 * @brief Create Enemy
 * This function initializes an enemy entity with necessary components.
*/
void Game::createEnemy(float x, float y, int type)
{
    enum EnemyType {
        BASIC = 1,
        FAST,
        TANK
    };
    switch (type) {
        case BASIC:
            GameHelper::createBasicEnemy(_world, x, y);
            break;
        case FAST:
            // Implement fast enemy creation
            break;
        case TANK:
            // Implement tank enemy creation
            break;
        default:
            std::cerr << "Unknown enemy type: " << type << std::endl;
            break;
    }
}
