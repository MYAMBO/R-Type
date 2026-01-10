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

#include "HP.hpp"
#include "Tag.hpp" 
#include "Text.hpp"
#include "Data.hpp"
#include "Layer.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Audio.hpp"
#include "Group.hpp"
#include "Music.hpp"
#include "Inputs.hpp"
#include "Sprite.hpp"
#include "Entity.hpp"
#include "Script.hpp"
#include "Camera.hpp"
#include "Button.hpp"
#include "Creator.hpp"
#include "Velocity.hpp"
#include "Position.hpp"
#include "Animator.hpp"
#include "Rotation.hpp"
#include "GameHelper.hpp"
#include "SoundEffect.hpp"
#include "BoxCollider.hpp"
#include "RectangleShape.hpp"
#include "ScriptsHandler.hpp"

#include "Draw.hpp"
#include "Mouse.hpp"
#include "Audio.hpp"
#include "Inputs.hpp"
#include "TextSys.hpp"
#include "Movement.hpp"
#include "CameraSys.hpp"
#include "GuiSystem.hpp"
#include "Animation.hpp"
#include "Collision.hpp"
#include "DeathSys.hpp"
#include "ScriptsSys.hpp"

#include "LevelLoader.hpp"

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
    _world.addSystem<ScriptsSys>();
    _world.addSystem<TextSystem>();
    _world.addSystem<Movement>();
    _world.addSystem<Animation>();
    _world.addSystem<Collision>();
    _world.addSystem<DeathSys>();
    _world.addSystem<Mouse>();
    _world.addSystem<Inputs>();
    _world.addSystem<Draw>();
    _world.addSystem<GuiSystem>(_window);
    _world.addSystem<Audio>();
}

/**
 * @brief Destroys the Game object.
 */
Game::~Game()
{
    _window.close();
}

/**
 * @brief Updates the ECS loading screen entities with a professional AAA look.
 */
void Game::updateLoadingState(float progress, const std::string& status)
{
    float width = static_cast<float>(_window.getSize().x);
    float height = static_cast<float>(_window.getSize().y);
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;
    float barFullWidth = 600.f;

    auto statusEnt = GameHelper::getEntityByTag(_world, "loading_status");
    if (statusEnt) {
        auto textComp = statusEnt->getComponent<Text>();
        auto posComp = statusEnt->getComponent<Position>();
        if (textComp && posComp) {
            textComp->setString(status);
            textComp->setColor(0, 255, 255, 255);
            posComp->setX(centerX - textComp->getGlobalBounds().size.x / 2.0f);
            posComp->setY(centerY - 50.f);
        }
    }

    auto bgBarEnt = GameHelper::getEntityByTag(_world, "loading_bg_bar");
    if (bgBarEnt) {
        auto bgRect = bgBarEnt->getComponent<RectangleShape>();
        auto bgPos = bgBarEnt->getComponent<Position>();
        if (bgRect && bgPos) {
            bgRect->setSize(barFullWidth, 20.f);
            bgRect->setColor(20, 20, 40, 255);
            bgPos->setX(centerX - (barFullWidth / 2.0f));
            bgPos->setY(centerY + 40.f);
        }
    }

    auto barEnt = GameHelper::getEntityByTag(_world, "loading_bar");
    if (barEnt) {
        auto rectComp = barEnt->getComponent<RectangleShape>();
        auto posComp = barEnt->getComponent<Position>();
        if (rectComp && posComp) {
            rectComp->setSize(barFullWidth * progress, 20.f);
            rectComp->setColor(0, 255, 255, 255);
            posComp->setX(centerX - (barFullWidth / 2.0f));
            posComp->setY(centerY + 40.f);
        }
    }
    _window.clear(sf::Color(5, 5, 15)); 
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

    _world.setCurrentScene(10);

    auto inputSystem = _world.getSystem<Inputs>();

    _creator.createMyambo();
    _creator.createKayu();
    int timeout = 180;

    while (_world.getCurrentScene() == 10) {
        _window.clear(sf::Color::Black);
        _world.manageSystems();
        gameInput(inputSystem);
        _window.display();
        timeout--;
        if (timeout <= 0)
            break;
    }
    _world.setCurrentScene(1000);
    timeout = 10;
    while (timeout > 0) {
        _window.clear(sf::Color::Black);
        _world.manageSystems();
        gameInput(inputSystem);
        _window.display();
        timeout--;
    }
    _world.setCurrentScene(11);
    timeout = 180;

    while (_world.getCurrentScene() == 11) {
        _window.clear(sf::Color::Black);
        _world.manageSystems();
        gameInput(inputSystem);
        _window.display();
        timeout--;
        if (timeout <= 0)
            break;
    }
    _world.setCurrentScene(0);

    _creator.createLoadingScreen();
    auto entermusic = _world.createEntity();
    entermusic->addComponent<SoundEffect>("../assets/sounds/loading.mp3", 100.f);
    entermusic->addComponent<Scene>(0);
    entermusic->addComponent<Tag>("entering_game_music");
    
    updateLoadingState(0.0f, "Initializing systems...");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    updateLoadingState(0.1f, "Loading assets...");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    _creator.createCamera();
    updateLoadingState(0.3f, "Generating Menu...");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    _creator.createTguiMenu();
    updateLoadingState(0.6f, "Generating Background...");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    _creator.createBackground(_window); 
    _creator.createCredits();
    updateLoadingState(0.8f, "Connecting to server...");
    
    Packet packet;
    packet.setId(0);
    packet.setAck(0);
    packet.setPacketNbr(1);
    packet.setTotalPacketNbr(1);
    packet.positionSpawn(0, Player, 300, 300);
    _network.sendPacket(packet);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    entermusic->getComponent<SoundEffect>()->play();
    updateLoadingState(1.0f, "Ready!");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    _world.setCurrentScene(42);
    auto musicmenu = GameHelper::getEntityByTag(_world, "menu_music");
    if (musicmenu) {
        auto musicComp = musicmenu->getComponent<Music>();
        if (musicComp)
            musicComp->play();
    }
    while (_window.isOpen()) {
        _window.clear(sf::Color::Black);
        gameInput(inputSystem);
        _world.manageSystems();
        _window.display();
        printf("sizewindow: %d sizeheight: %d\n", _window.getSize().x, _window.getSize().y);
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
    auto guiSystem = _world.getSystem<GuiSystem>();

    while (const std::optional eventOpt = _window.pollEvent()) {
        _world.setEvent(*eventOpt);
        if (inputSystem->isKeyPressed(KeyboardKey::Key_Escape) && _world.getCurrentScene() == 2)
            _window.close();
        else if (inputSystem->isKeyPressed(KeyboardKey::Key_Escape)
            && _world.getCurrentScene() != 2 && _world.getCurrentScene() != 10
            && _world.getCurrentScene() != 11) {
            _world.setCurrentScene(2);
        }
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
        if (guiSystem) {
            guiSystem->handleEvent(*eventOpt, _window);
        }
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
        auto dataComp = compPlayer->getComponent<Data>();
        if (!isShootKeyPressed && dataComp && std::stoi(dataComp->getData("mana")) >= 20) {
            Packet packet;
            packet.shoot(compPlayer->getId());
            packet.setAck(0);
            packet.setId(compPlayer->getId());
            packet.setPacketNbr(1);
            packet.setTotalPacketNbr(1);
            _network.sendPacket(packet);
            isShootKeyPressed = true;
            compPlayer->getComponent<SoundEffect>()->play();
            int mana = std::stoi(dataComp->getData("mana"));
            if (mana >= 20) {
                mana -= 20;
                if (mana < 0)
                    mana = 0;
                dataComp->setData("mana", std::to_string(mana));
            }
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
    playerScript(entityId, world);
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

void Game::setMusicVolume(int volume)
{
    _musicVolume = volume;
}

void Game::setSfxVolume(int volume)
{
    _sfxVolume = volume;
}

int Game::getMusicVolume()
{
    return _musicVolume;
}

int Game::getSfxVolume()
{
    return _sfxVolume;
}