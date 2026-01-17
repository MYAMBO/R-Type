/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** main of the game
*/

#include "Game.hpp"

#include <cmath>
#include <thread>
#include <fstream>
#include <json.hpp>
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
#include "Data.hpp"
#include "Scene.hpp"
#include "Action.hpp"
#include "Audio.hpp"
#include "Music.hpp"
#include "Inputs.hpp"
#include "Entity.hpp"
#include "Script.hpp"
#include "Camera.hpp"
#include "Button.hpp"
#include "Factory.hpp"
#include "Velocity.hpp"
#include "Position.hpp"
#include "GameHelper.hpp"
#include "SoundEffect.hpp"
#include "RectangleShape.hpp"
#include "ScriptsHandler.hpp"
#include "GameHelperGraphical.hpp"

#include "Mouse.hpp"
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
    : _window(sf::VideoMode({width, height}), title), _network(network), _factory(_world)
{
    _world.addSystem<CameraSys>();
    _world.addSystem<Audio>();
    _world.addSystem<ScriptsSys>();
    _world.addSystem<TextSystem>();
    _world.addSystem<Movement>();
    _world.addSystem<Mouse>();
    _world.addSystem<Inputs>();
    _world.addSystem<Animation>();
    _world.addSystem<Draw>();
    _world.addSystem<GuiSystem>(_window);
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

void Game::loadingRun()
{
    _window.setFramerateLimit(30);
    _world.setWindow(_window);
    _world.setDeltaTime(1.f);
    _factory.createGameTools();

    _world.setCurrentScene(static_cast<int>(SceneType::MENU));

    loadfile();
    auto inputSystem = _world.getSystem<Inputs>();

    _factory.createMyambo();
    _factory.createKayu();
    int timeout = 180;

    while (_world.getCurrentScene() == static_cast<int>(SceneType::MYAMBO)) {
        _window.clear(sf::Color::Black);
        _world.manageSystems();
        gameInput(inputSystem);
        _window.display();
        timeout--;
        if (timeout <= 0)
            break;
    }
    _world.setCurrentScene(static_cast<int>(SceneType::MENU));
    timeout = 10;
    while (timeout > 0) {
        _window.clear(sf::Color::Black);
        _world.manageSystems();
        gameInput(inputSystem);
        _window.display();
        timeout--;
    }
    _world.setCurrentScene(static_cast<int>(SceneType::MENU));
    timeout = 180;

    while (_world.getCurrentScene() == static_cast<int>(SceneType::KAYU)) {
        _window.clear(sf::Color::Black);
        _world.manageSystems();
        gameInput(inputSystem);
        _window.display();
        timeout--;
        if (timeout <= 0)
            break;
    }
    _world.setCurrentScene(static_cast<int>(SceneType::MENU));

    _factory.createLoadingScreen();

    updateLoadingState(0.0f, "Initializing systems...");
    //std::this_thread::sleep_for(std::chrono::milliseconds(300));
    updateLoadingState(0.1f, "Loading assets...");
    //std::this_thread::sleep_for(std::chrono::milliseconds(300));
    _factory.createCamera();
    updateLoadingState(0.3f, "Generating Menu...");
    //std::this_thread::sleep_for(std::chrono::milliseconds(300));
    _factory.createMenu();
    _factory.createLevelCompanionUI();
    updateLoadingState(0.6f, "Generating Background...");
    //std::this_thread::sleep_for(std::chrono::milliseconds(300));
    _factory.createCredits();
    _factory.createPlayerHUD();
    _factory.createScrapUIEmpty(1);
    _factory.createScrapUIEmpty(2);
    _factory.createScrapUIEmpty(3);
    _factory.createBackGameUI();
    _factory.createScoreDisplay();
    GameHelperGraphical::createStarField(_world);
    updateLoadingState(0.8f, "Connecting to server...");
    Packet packet;

    run();
}

/**
 * @brief Runs the main game loop.
 *
 * This function initializes the game, handles loading screens,
 * and enters the main game loop to process input and update the world.
 */
void Game::run()
{
    auto inputSystem = _world.getSystem<Inputs>();
    auto entermusic = _world.createEntity();
    entermusic->addComponent<SoundEffect>("../assets/sounds/loading.mp3", 100.f);
    entermusic->addComponent<Scene>(static_cast<int>(SceneType::LOADING));
    entermusic->addComponent<Tag>("entering_game_music");

    Packet packet;
    packet.setId(0);
    packet.setAck(0);
    packet.setPacketNbr(1);
    packet.setTotalPacketNbr(1);
    packet.Spawn(0, Player, 300, 300);
    _network.sendPacket(packet);

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    entermusic->getComponent<SoundEffect>()->play();
    updateLoadingState(1.0f, "Ready!");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    _world.setCurrentScene(static_cast<int>(SceneType::MENU));
    auto musicmenu = GameHelper::getEntityByTag(_world, "menu_music");
    if (musicmenu) {
        auto musicComp = musicmenu->getComponent<Music>();
        if (musicComp)
            musicComp->play();
    }
    _factory.createPlayerHUD();
    while (_window.isOpen()) {
        _window.clear(sf::Color::Black);
        gameInput(inputSystem);
        _world.manageSystems();
        _window.display();
    }
    savefile();
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
        if (inputSystem->isTriggered(*eventOpt, KeyboardKey::Key_Escape)) {
            int currentScene = _world.getCurrentScene();
            if (currentScene == static_cast<int>(SceneType::MENU)) {
                _window.close();
            } else if (currentScene != static_cast<int>(SceneType::MYAMBO) && currentScene != static_cast<int>(SceneType::KAYU)) {
                _world.setCurrentScene(static_cast<int>(SceneType::MENU));
            }
        }
        if (eventOpt->is<sf::Event::Closed>())
            _window.close();
        if (guiSystem) {
            guiSystem->handleEvent(*eventOpt, _window);
        }
        if (eventOpt->is<sf::Event::Resized>()) {
            sf::FloatRect visibleArea({0, 0}, {static_cast<float>(_window.getSize().x), static_cast<float>( _window.getSize().y)});
            _window.setView(sf::View(visibleArea));
        }
        // temporary testing code
        if (inputSystem->isTriggered(*eventOpt, KeyboardKey::Key_M)) {
            //GameHelperGraphical::createAnimatorEntity(_world, 400, 400, "../assets/sprites/green_effect.png", 5, 5, 2.f, 478, 154, 20, 20, 0, 0, 10.f);
            //GameHelperGraphical::createAnimatorEntity(_world, 400, 400, "../assets/sprites/r-typesheet1.gif", 7, 7, 2.f, 209, 276, 16, 14, 0, 0, 10.f);
            //GameHelperGraphical::createScoreGUI(_world, 400, 300, "1000");
            //GameHelperGraphical::createAnimatorEntity(_world, 200, 200, "../assets/sprites/fire_effect.png", 2, 2, 1.f, 223, 0, 16, 16, 0, 0, 10.f);
            _factory.createScraps(_world, 500.f, 0.f);
           
        }
        inputSystem->update(0.0f, _world);
    }
}

/**
 * @brief Creates the player entity.
 *
 * This function initializes the player entity with necessary components.
 */
void Game::smootherMovement(int entityId, World &world, float serverX, float serverY)
{
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity)
        return;
    auto pos = entity->getComponent<Position>();
    if (!pos)
        return;
    if (!entity->getComponent<Velocity>()) {
        pos->setX(serverX);
        pos->setY(serverY);
        return;
    }

    float dist = std::hypot(serverX - pos->getX(), serverY - pos->getY());
    if (dist > 100.0f) {
        pos->setX(serverX);
        pos->setY(serverY);
    }
    pos->setTargetX(serverX);
    pos->setTargetY(serverY);
}

void Game::updateEntity(uint32_t id, uint16_t type, float x, float y)
{
    if (type == 0) {
        auto entity = GameHelper::getEntityById(_world, id);
        if (entity) {
            smootherMovement(id, _world, x, y);
        }
        return;
    }
    auto entity = GameHelper::getEntityById(_world, id);
    if (entity) {
        auto hpComp = entity->getComponent<HP>();
        if (hpComp && !hpComp->isAlive()) {
            _world.killEntity(id);
        } else {
            smootherMovement(id, _world, x, y);
            return;
        }
    }
    switch (type) {
    case Player:
        _factory.createPlayer(id);
        entity = GameHelper::getEntityById(_world, id);
        if (entity && entity->getComponent<Tag>()->getTag() == "player") {
            entity->addComponent<Script>([this](const int entityId, World& world)
            {
                this->playerInput(entityId, world);
            });
        }
        break;
    case Enemy:
        _factory.createEnemy(x, y, 1, id);
        break;
    case Fast:
        _factory.createEnemy(x, y, 2, id);
        break;
    case Tank:
        _factory.createEnemy(x, y, 3, id);
        break;
    case EnemySinus:
        _factory.createEnemy(x, y, 4, id);
        break;
    case ShootingEnemy:
        _factory.createEnemy(x, y, 5, id);
        break;
    case Bullet:
        _factory.createBullet(id, x, y, type);
        break;
    case EnemyBullet:
        _factory.createEnemyBullet(id, x, y);
        break;
    case PortalBoss:
        _factory.createEnemy(x, y, 6, id);
        break;
    case HealPU:
        _factory.createPowerUp(x, y, 1, id);
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
    if (world.getCurrentScene() != static_cast<int>(SceneType::GAMEPLAY))
        return;
    static bool isShootKeyPressed = false;

    auto inputSystem = world.getSystem<Inputs>();
    std::shared_ptr<Camera> compCam = GameHelperGraphical::getMainCamera(world);
    std::shared_ptr<Entity> compPlayer = GameHelper::getEntityByTag(world, "player");
    auto settings = GameHelper::getEntityByTag(world, "game_controls_settings");
    auto data = settings->getComponent<Data>();

    if (!compCam || !compPlayer || !inputSystem || !data)
        return;

    auto pos = compPlayer->getComponent<Position>();
    auto vel = compPlayer->getComponent<Velocity>();

    float targetVx = 0.0f;
    float targetVy = 0.0f;
    bool moved = false;


    if (inputSystem->isKeyPressed(inputSystem->stringToKey(data->getData("RIGHT")))) {
        if (compCam->getPosition().x + compCam->getSize().x > pos->getX() + 7.0f) {
            targetVx = 7.0f;
            moved = true;
        }
    }
    if (inputSystem->isKeyPressed(inputSystem->stringToKey(data->getData("LEFT")))) {
        if (compCam->getPosition().x < pos->getX() - 7.0f) {
            targetVx = -7.0f;
            moved = true;
        }
    }
    if (inputSystem->isKeyPressed(inputSystem->stringToKey(data->getData("UP")))) {
        if (compCam->getPosition().y < pos->getY() - 7.0f) {
            targetVy = -7.0f;
            moved = true;
        }
    }
    if (inputSystem->isKeyPressed(inputSystem->stringToKey(data->getData("DOWN")))) {
        if (compCam->getPosition().y + compCam->getSize().y > pos->getY() + 7.0f) {
            targetVy = 7.0f;
            moved = true;
        }
    }
    vel->setVelocityX(targetVx);
    vel->setVelocityY(targetVy);

    if (inputSystem->isKeyPressed(inputSystem->stringToKey(data->getData("SHOOT")))) {
        auto dataComp = compPlayer->getComponent<Data>();
        if (!isShootKeyPressed && dataComp && std::stoi(dataComp->getData("mana")) >= 20) {
            Packet packet;
            packet.action(compPlayer->getId(), FIRE, 0);
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
            auto group = GameHelper::getEntitiesByGroup(world, compPlayer->getComponent<Group>()->getId());
            for (auto& entity : group) {
                if (entity->getComponent<Tag>()->getTag() == "companion") {
                    _factory.createLasersCompanion(entity->getId(), compPlayer->getId());
                }
            }
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

static void addScore(World &w, int entityId)
{
    auto stats = GameHelper::getEntityByTag(w, "game_stats");
    auto entity = GameHelper::getEntityById(w, entityId);
    if (!stats || !entity)
        return;
    auto dataComp = stats->getComponent<Data>();
    auto entityData = entity->getComponent<Data>();
    if (!entityData || !dataComp)
        return;
    int currentScore = std::stoi(dataComp->getData("score"));
    currentScore += std::stoi(entityData->getData("score"));
    dataComp->setData("score", std::to_string(currentScore));
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

    auto name = entity->getComponent<Tag>();
    if (name && name->getTag() == "enemy") {
        auto pos = entity->getComponent<Position>();
        GameHelperGraphical::createAnimatorEntity(_world, pos->getX(), pos->getY(), "../assets/sprites/r-typesheet1.gif", 5, 5, 2.f, 288, 295, 31, 32, 3, 0, 3.f);
        auto data = entity->getComponent<Data>();
        if (!data) {
            _world.killEntity(id);
            return -1;
        }
        GameHelperGraphical::createScoreGUI(_world, pos->getX(), pos->getY(), data->getData("score"));
        GameHelperGraphical::soundEffectEntity(data->getData("death_sound"), 100.f, _world.getCurrentScene(), _world);
        addScore(_world, id);
    }
    if (name && name->getTag() == "player_bullet") {
        auto pos = entity->getComponent<Position>();
        if (pos->getX() > _world.getWindow()->getSize().x || pos->getY() > _world.getWindow()->getSize().y || pos->getX() < 0 || pos->getY() < 0) {
            _world.killEntity(id);
            return 0;
        }
        GameHelperGraphical::createAnimatorEntity(_world, pos->getX(), pos->getY(), "../assets/sprites/r-typesheet1.gif", 7, 7, 2.f, 209, 276, 16, 14, 0, 0, 3.5f);
        GameHelperGraphical::soundEffectEntity("../assets/sounds/bullet_hit.mp3", 50.f, _world.getCurrentScene(), _world);
    }
    if (name && name->getTag() == "enemy_bullet") {
        auto pos = entity->getComponent<Position>();
        if (pos->getX() > _world.getWindow()->getSize().x || pos->getY() > _world.getWindow()->getSize().y || pos->getX() < 0 || pos->getY() < 0) {
            _world.killEntity(id);
            return 0;
        }
        GameHelperGraphical::createAnimatorEntity(_world, pos->getX(), pos->getY(), "../assets/sprites/r-typesheet1.gif", 7, 7, 2.f, 209, 276, 16, 14, 0, 0, 3.5f);
        GameHelperGraphical::soundEffectEntity("../assets/sounds/bullet_hit.mp3", 50.f, _world.getCurrentScene(), _world);
    }
    if (name && name->getTag() == "heal") {
        auto pos = entity->getComponent<Position>();
        GameHelperGraphical::createAnimatorEntity(_world, pos->getX(), pos->getY(), "../assets/sprites/green_effect.png", 5, 5, 2.f, 478, 154, 20, 20, 0, 0, 4.f);
        GameHelperGraphical::soundEffectEntity("../assets/sounds/heal.mp3", 75.f, _world.getCurrentScene(), _world);
    }
    _world.killEntity(id);
    return 0;
}

void Game::savefile()
{
    nlohmann::json save;
    std::vector<std::string> tagsToSave = {
        "game_volume_settings",
        "game_controls_settings",
        "game_availability_settings"
    };
    for (const auto& tag : tagsToSave) {
        auto entity = GameHelper::getEntityByTag(_world, tag);
        if (entity) {
            auto dataComp = entity->getComponent<Data>();
            if (dataComp) {
                save[tag] = dataComp->getDataSet();
            }
        }
    }
    std::ofstream file("settings.json");
    if (file.is_open()) {
        file << save.dump(4);
        file.close();
        std::cout << "[Config] Settings saved to settings.json" << std::endl;
    } else {
        std::cerr << "[Config] ERROR: Could not open settings.json for writing" << std::endl;
    }
}

void Game::loadfile()
{
    std::ifstream file("settings.json");
    if (!file.is_open()) {
        std::cout << "[Config] No settings file found, using default values." << std::endl;
        return;
    }
    try {
        nlohmann::json save;
        file >> save;
        file.close();
        for (auto& [tag, settings] : save.items()) {
            auto entity = GameHelper::getEntityByTag(_world, tag);
            if (entity) {
                auto dataComp = entity->getComponent<Data>();
                if (dataComp) {
                    for (auto& [key, value] : settings.items()) {
                        dataComp->setData(key, value.get<std::string>());
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[Config] ERROR while loading settings: " << e.what() << std::endl;
    }
}

void Game::handleAction(const uint32_t id, const uint8_t action, const uint32_t data)
{
    switch (action) {
        case HEAL: {
            healEntity(id, data);
            break;
        }
        case BEAM: {
            break;
        }
        case SHIELD: {
            break;
        }
        default:
            break;
    }
}

void Game::healEntity(const uint32_t entityId, const uint32_t newHp)
{
    const auto entity = GameHelper::getEntityById(_world, entityId);
    if (!entity) return;

    auto hp = entity->getComponent<HP>();
    if (!hp)
        return;
    hp->setHP(newHp);
    std::cout << "Entity " << entityId << " HP set to: " << newHp << std::endl;
}

void Game::updatePlayerMana(uint32_t playerId, int mana)
{
    auto player = GameHelper::getEntityById(_world, playerId);
    if (!player)
        return;

    auto dataComp = player->getComponent<Data>();
    if (dataComp)
        dataComp->setData("mana", std::to_string(mana));
}
