/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** main of the game
*/

#include "Game.hpp"

#include <cmath>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "iostream"

#include "HP.hpp"
#include "Tag.hpp"
#include "Draw.hpp"
#include "Text.hpp"
#include "Layer.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Action.hpp"
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
#include "RectangleShape.hpp"
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
#include "DeathSys.hpp"

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
    _world.addSystem<DeathSys>();
    _world.addSystem<Mouse>();
    _world.addSystem<Inputs>();
    _world.addSystem<Draw>();
}

/**
 * @brief Destroys the Game object.
 */
Game::~Game()
{
    _window.close();
}
/**
 * @brief Updates the ECS loading screen entities and forces a frame render.
 */
void Game::updateLoadingState(float progress, const std::string& status)
{
    auto statusEnt = GameHelper::getEntityByTag(_world, "loading_status");
    if (statusEnt) {
        auto textComp = statusEnt->getComponent<Text>();
        if (textComp) textComp->setString(status);

        auto posComp = statusEnt->getComponent<Position>();
        sf::FloatRect bounds = textComp->getGlobalBounds();
        float centerX = _window.getSize().x / 2.0f - 200.f;
        if (posComp)
            posComp->setX(centerX - (bounds.size.x / 2.0f));
    }

    auto barEnt = GameHelper::getEntityByTag(_world, "loading_bar");
    if (barEnt) {
        auto rectComp = barEnt->getComponent<RectangleShape>();
        if (rectComp) {
            rectComp->setSize(400.f * progress, 20.f);
        }
    }

    _window.clear(sf::Color::Black);
    _world.manageSystems();
    _window.display();
}

/**
 * @brief Runs the main game loop.
 *
 * This function initializes the game, handles loading screens,
 * and enters the main game loop to process input and update the world.
 */
void Game::run()
{
    _window.setFramerateLimit(30);
    _world.setWindow(_window);
    _world.setDeltaTime(1.f);

    _world.setCurrentScene(0);
    _creator.createLoadingScreen();

    updateLoadingState(0.0f, "Initializing systems...");
    updateLoadingState(0.1f, "Loading assets...");
    _creator.createCamera();
    updateLoadingState(0.3f, "Generating Menu...");
    _creator.createMenu();
    updateLoadingState(0.6f, "Generating Background...");
    _creator.createBackground(_window);
    updateLoadingState(0.8f, "Connecting to server...");

    Packet packet;
    packet.setId(0);
    packet.setAck(0);
    packet.setPacketNbr(1);
    packet.setTotalPacketNbr(1);
    packet.Spawn(0, Player, 300, 300);
    _network.sendPacket(packet);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    updateLoadingState(1.0f, "Ready!");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    _world.setCurrentScene(2);
    auto inputSystem = _world.getSystem<Inputs>();

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
        if (inputSystem->isKeyPressed(KeyboardKey::Key_E)) {
            static sf::Clock spawnClock;
            if (spawnClock.getElapsedTime().asSeconds() > 0.5f) {
                _creator.createEnemy(800.0f, 300.0f, 1);
                std::cout << "[Debug] Enemy spawned at (800, 300)" << std::endl;
                spawnClock.restart();
            }
        }

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
void Game::createPlayer(uint32_t id)

void Game::smootherMovement(int entityId, World &world, float serverX, float serverY)
{
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity) return;
    if (!entity->getComponent<Velocity>()) {
        auto pos = entity->getComponent<Position>();
        pos->setX(serverX);
        pos->setY(serverY);
        return;
    static int playerCount = 0;
    if (playerCount >= 4)
        return;
    auto player = _world.createEntity(id);
    player->addComponent<HP>(100);
    player->addComponent<Position>(75.0f, 75.0f);
    player->addComponent<Sprite>(std::string("../sprites/r-typesheet42.gif"));
    player->addComponent<Scale>(2.f);
    player->addComponent<Scene>(1);
    player->addComponent<Layer>(10);
    player->addComponent<BoxCollider>(33.0f, 19.0f);
    
    printf("Creating player with id: %u\n", player->getId());
    if (playerCount == 0) {
        // Premier joueur (joueur local)
        player->addComponent<Animator>(2, 1, 3.f, 0, 0, 33, 19, 0, 0);
        player->addComponent<Script>([this](const uint32_t entityId, World& world)
        {
            this->playerInput(entityId, _world);
        });
        player->addComponent<Tag>("player");
    } else {
        // Autres joueurs (coéquipiers)
        player->addComponent<Animator>(2, 1, 3.f, 0, (playerCount * 17), 33, 19, 0, 0);
        player->addComponent<Tag>("player_mate");
    }
    auto pos = entity->getComponent<Position>();

    float dist = std::hypot(serverX - pos->getX(), serverY - pos->getY());

/**
 * @brief Create Enemy
 * This function initializes an enemy entity with necessary components.
*/
void Game::createEnemy(float x, float y, uint16_t type)
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
    if (dist > 100.0f) {
        pos->setX(serverX);
        pos->setY(serverY);
    }
    pos->setTargetX(serverX);
    pos->setTargetY(serverY);

}

void Game::handleSpawn(uint32_t id, uint16_t type, float x, float y)
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
void Game::playerInput(uint32_t entityId, World &world)
{
    if (world.getCurrentScene() != 1)
        return;
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
            packet.action(compPlayer->getId(), 1); // 1 for Shoot or default action
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
        Packet packet = Packet();
        packet.updatePosition(entityId, pos->getX(), pos->getY());
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

void Game::handleAction(const uint32_t id, const uint8_t action, const uint32_t data)
{
    switch (action) {
        case HEAL: {
            healEntity(id, data);
        }
        case BEAM: {

        }
        case SHIELD: {

        }
    }
}

void Game::healEntity(const uint32_t entityId, const uint32_t amount)
{
    const auto entity = GameHelper::getEntityById(_world, entityId);

    const unsigned int hpMax = entity->getComponent<HP>()->getMaxHP();
    const unsigned int actualHp = entity->getComponent<HP>()->getHP();

    if (actualHp + amount > hpMax) {
        entity->getComponent<HP>()->setHP(hpMax);
    } else {
        entity->getComponent<HP>()->setHP(actualHp + amount);
    }
}
