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
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include "HP.hpp"
#include "Tag.hpp" 
#include "Draw.hpp"
#include "Layer.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Inputs.hpp"
#include "Sprite.hpp"
#include "Entity.hpp"
#include "Script.hpp"
#include "Camera.hpp"
#include "Updater.hpp"
#include "Velocity.hpp"
#include "Position.hpp"
#include "Animator.hpp"
#include "Rotation.hpp"
#include "GameHelper.hpp"
#include "BoxCollider.hpp"
#include "Collision.hpp"
#include "ScriptsHandler.hpp"


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
    : _window(sf::VideoMode({width, height}), title), _network(network)
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
 * @brief Create Background
 * This function initializes the background entities with necessary components.
*/
void Game::createBackground()
{
    auto backgroundFirst = _world.createEntity();
    backgroundFirst->addComponent<Sprite>(std::string("../sprites/background.png"));
    
    auto windowSize = _window.getSize();
    auto spriteComp = backgroundFirst->getComponent<Sprite>();
    auto boundsSize = spriteComp->getSprite()->getGlobalBounds(); 
    float scaleX = static_cast<float>(windowSize.x) / boundsSize.size.x;
    float scaleY = static_cast<float>(windowSize.y) / boundsSize.size.y;
    float finalScale = std::max(scaleX, scaleY);
    if (finalScale < 1.0f)
        finalScale = 1.0f;
    backgroundFirst->addComponent<Scale>(finalScale);

    backgroundFirst->addComponent<Scene>(_world.getCurrentScene());
    backgroundFirst->addComponent<Position>(0.f, 0.f);
    backgroundFirst->addComponent<Script>(backgroundScrollScript);
    backgroundFirst->addComponent<Layer>(LayerType::BACKGROUND);
    backgroundFirst->addComponent<Velocity>(-4.f, 0.f);
    backgroundFirst->addComponent<Tag>("background_first");
    auto backgroundSecond = _world.createEntity();
    backgroundSecond->addComponent<Sprite>(std::string("../sprites/background.png"));
    backgroundSecond->addComponent<Scale>(1.f);
    backgroundSecond->addComponent<Scene>(_world.getCurrentScene());
    auto bounds = backgroundFirst->getComponent<Sprite>()->getSprite()->getGlobalBounds();
    backgroundSecond->addComponent<Position>(bounds.size.x - 10.f, 0.f);
    backgroundSecond->addComponent<Velocity>(-4.f, 0.f);
    backgroundSecond->addComponent<Script>(backgroundScrollScript);
    backgroundSecond->addComponent<Layer>(LayerType::BACKGROUND);
    backgroundSecond->addComponent<Tag>("background_second");
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
    createCamera();
    createBackground();
    _world.addSystem<Collision>();
    _world.addSystem<Updater>();
    _world.addSystem<Draw>();
    _world.addSystem<Inputs>();
    _window.setFramerateLimit(30);
    _world.setDeltaTime(1.f);
    auto inputSystem = _world.getSystem<Inputs>();
    _world.setWindow(_window);
    _world.setCurrentScene(1);
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

/**
 * @brief Creates the player entity.
 * 
 * This function initializes the player entity with necessary components.
 */
void Game::createPlayer()
{
    static int playerCount = 0;
    if (playerCount >= 4)
        return;
    auto player = _world.createEntity();
    player->addComponent<HP>(100);
    player->addComponent<Position>(75.0f, 75.0f);
    player->addComponent<Sprite>(std::string("../sprites/r-typesheet42.gif"));
    player->addComponent<Scale>(2.f);
    player->addComponent<Scene>(1);
    player->addComponent<Layer>(10);
    player->addComponent<BoxCollider>(33.0f, 19.0f);
    
    if (playerCount == 0) {
        player->addComponent<Animator>(2, 1, 3.f, 0, 0, 33, 19, 0, 0);
        player->addComponent<Script>(
            [this](const int entityId, World &world)
            {
                this->playerInput(entityId, world);
            }
        );
        player->addComponent<Tag>("player");
    } else {
        player->addComponent<Animator>(2, 1, 3.f, 0, (playerCount * 17), 33, 19, 0, 0);
        player->addComponent<Tag>("player_mate");
    }
    
    playerCount++;
    
    auto fire = _world.createEntity();
    fire->addComponent<Position>(0.f, 85.f);
    fire->addComponent<Sprite>(std::string("../sprites/r-typesheet1.gif"));
    fire->addComponent<Animator>(2, 1, 3.f, 285, 85, 15, 15, 0, 0);
    fire->addComponent<Scale>(2.f);
    fire->addComponent<Scene>(1);
    fire->addComponent<BoxCollider>(15.f, 15.f);
    fire->addComponent<Script>(playerfire);
    fire->addComponent<Layer>(10);
    fire->addComponent<Tag>("fire");
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

/**
 * @brief Handles player input.
 *
 * This function processes user input events and updates the game state accordingly.
 * @param inputSystem The input system to check for player actions.
 */
void Game::playerInput(int entityId, World &world)
{
    (void)entityId;
    static bool isShootKeyPressed = false;
    auto inputSystem = world.getSystem<Inputs>();
    std::shared_ptr<Camera> compCam = GameHelper::getMainCamera(world);
    if (!compCam)
        return;

    std::shared_ptr<Entity> compPlayer = GameHelper::getEntityByTag(world, "player");
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
        if (!isShootKeyPressed) {
            createBullet(compPlayer->getId(), world);
            Packet packet;
            packet.shoot(compPlayer->getId());
            packet.setId(compPlayer->getId());
            packet.setAck(0);
            packet.setPacketNbr(1);
            packet.setTotalPacketNbr(1);
            _network.sendPacket(packet);
            isShootKeyPressed = true;
        }
    } else {
        isShootKeyPressed = false;
    }
}


void Game::UpdatePosition(int id, float x, float y)
{
    auto entity = GameHelper::getEntityById(_world, id);
    if (entity) {
        auto positionComp = entity->getComponent<Position>();
        if (positionComp) {
            positionComp->setX(x);
            positionComp->setY(y);
        }
    }
}

void Game::handleSpawn(int id, int type, float x, float y)
{
    switch (type) {
        case None:
            UpdatePosition(id, x, y);
            break;
        case Player:
            std::cout << "Spawning player at position (" << x << ", " << y << ")" << std::endl;
            createPlayer();
            break;
        case Enemy:
            std::cout << "Spawning enemy at position (" << x << ", " << y << ")" << std::endl;
            createEnemy(x, y, 1); // Type 1 = BASIC enemy
            break;
        case Bullet:
            std::cout << "Spawning bullet" << std::endl;
            createBullet(id, _world);
            break;
    }
}
