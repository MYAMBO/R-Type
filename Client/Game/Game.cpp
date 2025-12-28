/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** main of the game
*/

#include "Game.hpp"

#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "HP.hpp"
#include "Tag.hpp" 
#include "Text.hpp"
#include "Layer.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Group.hpp"
#include "Inputs.hpp"
#include "Sprite.hpp"
#include "Entity.hpp"
#include "Script.hpp"
#include "Camera.hpp"
#include "Button.hpp"
#include "Velocity.hpp"
#include "Position.hpp"
#include "Animator.hpp"
#include "Rotation.hpp"
#include "GameHelper.hpp"
#include "Creator.hpp"
#include "BoxCollider.hpp"
#include "ScriptsHandler.hpp"

#include "Draw.hpp"
#include "Mouse.hpp"
#include "Inputs.hpp"
#include "TextSys.hpp"
#include "Movement.hpp"
#include "CameraSys.hpp"
#include "Animation.hpp"
#include "Collision.hpp"
#include "ScriptsSys.hpp"

/**
 * @brief Constructs a new Game object.
 *
 * Initializes the game window with specified dimensions and title.
 * @param network The class containing methods to send packet
 * @param width The width of the game window in pixels. Default is 800.
 * @param height The height of the game window in pixels. Default is 600.
 * @param title The title of the game window. Default is "Game".
 */
Game::Game(IGameNetwork& network, unsigned int width, unsigned int height, const std::string& title)
    : _window(sf::VideoMode({width, height}), title), _network(network), _creator(_world)
{
    _world.addSystem<CameraSys>();
    _world.addSystem<TextSystem>();
    _world.addSystem<ScriptsSys>();
    _world.addSystem<Movement>();
    _world.addSystem<Animation>();
    _world.addSystem<Collision>();
    _world.addSystem<Mouse>();
    _world.addSystem<Draw>();
    _world.addSystem<Inputs>();
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
    Packet packet;
    packet.setId(0);
    packet.setAck(0);
    packet.setPacketNbr(1);
    packet.setTotalPacketNbr(1);
    packet.positionSpawn(0, Player, 300, 300);
    _network.sendPacket(packet);
    _creator.createCamera();
    _creator.createMenu();
    _creator.createBackground(_window);
    _window.setFramerateLimit(30);
    _world.setDeltaTime(1.f);
    auto inputSystem = _world.getSystem<Inputs>();
    _world.setWindow(_window);
    _world.setCurrentScene(2);
    while (_window.isOpen()) {
        _window.clear(sf::Color::Black);
        gameInput(inputSystem);
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
        if (inputSystem->isKeyPressed(KeyboardKey::Key_Escape))
            _window.close();
        if (eventOpt->is<sf::Event::Closed>())
            _window.close();
        if (eventOpt->is<sf::Event::Resized>()) {
            sf::FloatRect visibleArea({0, 0}, {static_cast<float>(_window.getSize().x), static_cast<float>( _window.getSize().y)});
            _window.setView(sf::View(visibleArea));
        }
        inputSystem->update(0.0f, _world);
    }
}


void Game::smootherMovement(int entityId, World &world, float serverX, float serverY)
{
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity) return;
    if (!entity->getComponent<Velocity>()) {
        printf("Entity with id %d has no Velocity component.\n", entityId);
        auto pos = entity->getComponent<Position>();
        pos->setX(serverX);
        pos->setY(serverY);
        return;
    }
    auto pos = entity->getComponent<Position>();

    float dist = std::hypot(serverX - pos->getX(), serverY - pos->getY());

    if (dist > 100.0f) {
        pos->setX(serverX);
        pos->setY(serverY);
    }
    pos->setTargetX(serverX);
    pos->setTargetY(serverY);

}

void Game::handleSpawn(int id, int type, float x, float y)
{
    switch (type) {
        case None:
            smootherMovement(id, _world, x, y);
            break;
        case Player : {
            _creator.createPlayer(id);
            auto entity = GameHelper::getEntityById(_world, id);
            if (entity->getComponent<Tag>()->getTag() == "player") {
                entity->addComponent<Script>([this](const int entityId, World& world)
                {
                    this->playerInput(entityId, world);
                });
            }
            break;
        }
        case Enemy:
            _creator.createEnemy(x, y, 1); // Type 1 = BASIC enemy
            break;
        case Bullet:
            _creator.createBullet(id, x, y, type);
            break;
    }
}

/**
 * @brief Handles player input for movement and shooting.
 *
 * This function processes input events to control the player's movement
 * and shooting actions, updating the player's velocity and sending
 * position updates to the server.
 * @param entityId The unique ID of the player entity.
 * @param world The game world containing entities and components.
 */
void Game::playerInput(int entityId, World &world)
{
    (void)entityId;
    static bool isShootKeyPressed = false;

    auto inputSystem = world.getSystem<Inputs>();
    std::shared_ptr<Camera> compCam = GameHelper::getMainCamera(world);
    std::shared_ptr<Entity> compPlayer = GameHelper::getEntityByTag(world, "player");

    if (!compCam || !compPlayer)
        return;

    auto pos = compPlayer->getComponent<Position>();
    auto vel = compPlayer->getComponent<Velocity>();

    float targetVx = 0.0f;
    float targetVy = 0.0f;
    bool moved = false;

    if (inputSystem->isKeyPressed(KeyboardKey::Key_D)) {
        if (compCam->getPosition().x + compCam->getSize().x > pos->getX() + 7.0f) {
            targetVx = 7.0f;
            moved = true;
        }
    }
    if (inputSystem->isKeyPressed(KeyboardKey::Key_Q)) {
        if (compCam->getPosition().x < pos->getX() - 7.0f) {
            targetVx = -7.0f;
            moved = true;
        }
    }
    if (inputSystem->isKeyPressed(KeyboardKey::Key_Z)) {
        if (compCam->getPosition().y < pos->getY() - 7.0f) {
            targetVy = -7.0f;
            moved = true;
        }
    }
    if (inputSystem->isKeyPressed(KeyboardKey::Key_S)) {
        if (compCam->getPosition().y + compCam->getSize().y > pos->getY() + 7.0f) {
            targetVy = 7.0f;
            moved = true;
        }
    }
    vel->setVelocityX(targetVx);
    vel->setVelocityY(targetVy);

    if (inputSystem->isKeyPressed(KeyboardKey::Key_Space)) {
        if (!isShootKeyPressed) {
            Packet packet;
            packet.shoot(compPlayer->getId());
            packet.setAck(0);
            packet.setId(compPlayer->getId());
            packet.setPacketNbr(1);
            packet.setTotalPacketNbr(1);
            _network.sendPacket(packet);
            isShootKeyPressed = true;
        }
    } else {
        isShootKeyPressed = false;
    }
    if (moved)
    {
        Packet packet;
        packet.playerPosition(entityId, pos->getX(), pos->getY());
        packet.setAck(1);
        packet.setId(compPlayer->getId());
        packet.setPacketNbr(1);
        packet.setTotalPacketNbr(1);
        _network.sendPacket(packet);
    }
}

/**
 * @brief Kills an entity by its ID.
 *
 * This function removes the entity with the specified ID from the game world.
 * @param id The unique ID of the entity to be killed.
*/
int Game::killEntity(int id)
{
    auto entity = GameHelper::getEntityById(_world, id);
    if (!entity)
        return -1;
    _world.killEntity(id);
    return 0;
}