/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Creator
*/

#include "Game.hpp"
#include "Creator.hpp"
#include "GameHelper.hpp"
#include "ScriptsHandler.hpp"

#include "HP.hpp"
#include "Tag.hpp"
#include "Data.hpp"
#include "Text.hpp"
#include "Scale.hpp"
#include "Layer.hpp"
#include "Group.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"
#include "Camera.hpp"
#include "Button.hpp"
#include "Script.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Animator.hpp"
#include "Rotation.hpp"
#include "BoxCollider.hpp"
#include "Damage.hpp"

Creator::Creator(World& world)
: _world(world)
{
}

/**
* @brief Helper function to create a standardized menu button
* @param label The text label of the button
* @param sceneId The scene ID where the button will be displayed
* @param x The x position of the button
* @param y The y position of the button
* @param onClick The callback function to be called when the button is clicked
 */
void Creator::createMenuButton(const std::string& label, int sceneId, float x, float y, const std::function<void()>& onClick)
{
    auto btnEntity = _world.createEntity();
    btnEntity->addComponent<Sprite>("../sprites/Elements-01.png");
    btnEntity->addComponent<Scale>(0.3f);
    btnEntity->addComponent<Scene>(sceneId);
    btnEntity->addComponent<Layer>(LayerType::UI);
    
    float width = (1200.f * 0.3f);
    float height = (500.f * 0.3f);
    
    float btnLeft = x - (width / 2.f);
    float btnTop = y;

    btnEntity->addComponent<Position>(btnLeft, btnTop);
    
    btnEntity->addComponent<Button>(width, height);
    auto btnComp = btnEntity->getComponent<Button>();

    sf::IntRect rect({100, 150}, {1200, 500});
    btnComp->setTextureRects(rect, rect, rect);
    btnComp->setColorStates(sf::Color::White, sf::Color(200, 200, 200), sf::Color(100, 100, 100));
    btnComp->setOnClick(onClick);

    auto textEntity = _world.createEntity();
    textEntity->addComponent<Scene>(sceneId);
    textEntity->addComponent<Layer>(LayerType::UI + 1);
    
    textEntity->addComponent<Text>(label, "../sprites/title.ttf", 30);
    
    auto textComp = textEntity->getComponent<Text>();
    sf::FloatRect bounds = textComp->getGlobalBounds();

    float textX = btnLeft + (width / 2.f) - (bounds.size.x / 2.f);
    float textY = btnTop + (height / 2.f) - (bounds.size.y / 2.f);

    textX -= bounds.position.x;
    textY -= bounds.position.y;
    textEntity->addComponent<Position>(textX, textY);
}

/**
 * @brief Create Menu (Scene 2)
 */
void Creator::createMenu()
{
    createOptions(); 

    auto window = _world.getWindow();
    unsigned int width = window->getSize().x;
    float centerX = static_cast<float>(width) / 2.0f;
    float btnX = centerX;

    auto titleEntity = _world.createEntity();
    titleEntity->addComponent<Scene>(2);
    titleEntity->addComponent<Layer>(LayerType::UI);
    titleEntity->addComponent<Text>("R-TYPE", "../sprites/title.ttf", 80);
    titleEntity->addComponent<Position>(centerX - titleEntity->getComponent<Text>()->getGlobalBounds().size.x / 2.0f, 100.f);
    titleEntity->getComponent<Text>()->setColor(sf::Color::Cyan);

    createMenuButton("PLAY", 2, btnX, 300.f, [this]() {
        _world.setCurrentScene(1);
    });
    
    createMenuButton("OPTIONS", 2, btnX, 450.f, [this]() {
        std::cout << "Switching to Options Scene" << std::endl;
        _world.setCurrentScene(3);
    });
    
    createMenuButton("QUIT", 2, btnX, 600.f, [this]() {
        std::cout << "Quit Clicked" << std::endl;
        if (_world.getWindow()) {
            _world.getWindow()->close();
        }
    });
}

std::shared_ptr<Entity> Creator::createStatusText(float y, bool initialState)
{
    auto window = _world.getWindow();
    unsigned int width = window->getSize().x;
    float centerX = static_cast<float>(width) / 2.0f;

    auto statusEntity = _world.createEntity();
    statusEntity->addComponent<Scene>(3);
    statusEntity->addComponent<Layer>(LayerType::UI);
    
    std::string label = initialState ? "ON" : "OFF";
    statusEntity->addComponent<Text>(label, "../sprites/title.ttf", 30);
    
    sf::Color color = initialState ? sf::Color::Green : sf::Color::Red;
    statusEntity->getComponent<Text>()->setColor(color);

    statusEntity->addComponent<Position>(centerX + 250.f, y + 15.f);
    return statusEntity;
}

/**
 * @brief Create Options (Scene 3)
 */
void Creator::createOptions()
{
    auto window = _world.getWindow();
    unsigned int width = window->getSize().x;
    float centerX = static_cast<float>(width) / 2.0f;

    auto titleEntity = _world.createEntity();
    titleEntity->addComponent<Scene>(3);
    titleEntity->addComponent<Layer>(LayerType::UI);
    titleEntity->addComponent<Text>("OPTIONS", "../sprites/title.ttf", 80);
    titleEntity->addComponent<Position>(centerX - 180.f, 50.f);
    titleEntity->getComponent<Text>()->setColor(sf::Color::Green);

    static bool godMode = false;
    static bool colorBlind = false;
    static bool easyMode = false;
    static bool hardMode = false;

    

    float godY = 200.f;
    auto godStatus = createStatusText(godY, godMode);

    createMenuButton("GOD MODE", 3, centerX, godY, [this, godStatus]() {
        godMode = !godMode;
        
        auto textComp = godStatus->getComponent<Text>();
        textComp->setString(godMode ? "ON" : "OFF");
        textComp->setColor(godMode ? sf::Color::Green : sf::Color::Red);

        auto entity = GameHelper::getEntityByTag(_world, "player");
        if (entity) {
            auto dataComp = entity->getComponent<Data>();
            if (dataComp) dataComp->setData("is_god_mode", godMode ? "true" : "false");
        }
    });

    float easyY = 325.f;
    float hardY = 450.f;
    
    auto easyStatus = createStatusText(easyY, easyMode);
    auto hardStatus = createStatusText(hardY, hardMode);

    createMenuButton("EASY MODE", 3, centerX, easyY, [this, easyStatus, hardStatus]() {
        easyMode = !easyMode;
        if (easyMode) hardMode = false;

        easyStatus->getComponent<Text>()->setString(easyMode ? "ON" : "OFF");
        easyStatus->getComponent<Text>()->setColor(easyMode ? sf::Color::Green : sf::Color::Red);

        hardStatus->getComponent<Text>()->setString(hardMode ? "ON" : "OFF");
        hardStatus->getComponent<Text>()->setColor(hardMode ? sf::Color::Green : sf::Color::Red);

        auto entity = GameHelper::getEntityByTag(_world, "player");
        if (entity) {
            auto dataComp = entity->getComponent<Data>();
            if (dataComp) {
                dataComp->setData("is_easy_mode", easyMode ? "true" : "false");
                dataComp->setData("is_hard_mode", hardMode ? "true" : "false");
            }
        }
        std::cout << "Difficulty set to: " << (easyMode ? "EASY" : "NORMAL") << std::endl;
    });

    createMenuButton("HARD MODE", 3, centerX, hardY, [this, easyStatus, hardStatus]() {
        hardMode = !hardMode;
        if (hardMode) easyMode = false;

        hardStatus->getComponent<Text>()->setString(hardMode ? "ON" : "OFF");
        hardStatus->getComponent<Text>()->setColor(hardMode ? sf::Color::Green : sf::Color::Red);

        easyStatus->getComponent<Text>()->setString(easyMode ? "ON" : "OFF");
        easyStatus->getComponent<Text>()->setColor(easyMode ? sf::Color::Green : sf::Color::Red);

        auto entity = GameHelper::getEntityByTag(_world, "player");
        if (entity) {
            auto dataComp = entity->getComponent<Data>();
            if (dataComp) {
                dataComp->setData("is_easy_mode", easyMode ? "true" : "false");
                dataComp->setData("is_hard_mode", hardMode ? "true" : "false");
            }
        }
        std::cout << "Difficulty set to: " << (hardMode ? "HARD" : "NORMAL") << std::endl;
    });

    float daltonianY = 575.f;
    auto daltStatus = createStatusText(daltonianY, colorBlind);

    createMenuButton("DALTONIAN", 3, centerX, daltonianY, [this, daltStatus]() {
        colorBlind = !colorBlind;

        auto textComp = daltStatus->getComponent<Text>();
        textComp->setString(colorBlind ? "ON" : "OFF");
        textComp->setColor(colorBlind ? sf::Color::Green : sf::Color::Red);

        auto entity = GameHelper::getEntityByTag(_world, "player");
        if (entity) {
            auto dataComp = entity->getComponent<Data>();
            if (dataComp) dataComp->setData("is_color_blind", colorBlind ? "true" : "false");
        }
        std::cout << "Colorblind Mode: " << (colorBlind ? "ON" : "OFF") << std::endl;
    });

    createMenuButton("RETURN", 3, centerX, 750.f, [this]() {
        std::cout << "Returning to Main Menu" << std::endl;
        _world.setCurrentScene(2);
    });
}

/**
 * @brief Creates the player entity.
 * 
 * This function initializes the player entity with necessary components.
 */
void Creator::createPlayer(uint64_t id)
{
    if (GameHelper::getEntityById(_world, id) != nullptr)
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
    player->addComponent<Group>(playerCount + 1);
    player->addComponent<Damage>(10);
    player->addComponent<BoxCollider>(33.0f, 19.0f);

    std::map<std::string, std::string> dataMap = {
        {"is_god_mode", "false"},
        {"is_easy_mode", "false"},
        {"is_color_blind", "false"},
        {"is_hard_mode", "false"}
    };
    player->addComponent<Data>(dataMap);
    
    if (playerCount == 0) {
        player->addComponent<Velocity>(0.f, 0.f);
        player->addComponent<Animator>(2, 1, 3.f, 0, 0, 33, 19, 0, 0);
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
    fire->addComponent<Script>(playerfire);
    fire->addComponent<Group>(playerCount);
    fire->addComponent<Layer>(10);
    fire->addComponent<Tag>("fire");
}

/**
 * @brief Create Background
 * This function initializes the background entities with necessary components.
*/
void Creator::createBackground(sf::RenderWindow& window)
{
    auto backgroundFirst = _world.createEntity();
    backgroundFirst->addComponent<Sprite>(std::string("../sprites/background.png"));
    
    auto windowSize = window.getSize();
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
 * @brief Create Enemy
 * This function initializes an enemy entity with necessary components.
*/
void Creator::createEnemy(float x, float y, int type)
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
 * @brief Create Camera
 * This function initializes a camera entity with necessary components.
*/
void Creator::createCamera()
{
    auto cameraEntity = _world.createEntity();
    cameraEntity->addComponent<Camera>(sf::Vector2f(1920.f, 1080.f), sf::Vector2f(0.f, 0.f));
    cameraEntity->addComponent<Tag>("main_camera");
}


/**
 * @brief Creates a bullet entity.
 *
 * This function initializes a bullet entity with necessary components.
 * @param entityId The ID of the entity that fired the bullet.
 */
void Creator::createBullet(size_t entityId, int x, int y, int type)
{
    auto entity = GameHelper::getEntityById(_world, entityId);
    if (entity)
        return;
    bool isPlayer = (type == Bullet);
    auto bullet = _world.createEntity(entityId);
    if (isPlayer) {
        bullet->addComponent<Position>(x, y);
        bullet->addComponent<Velocity>(10.f, 0.f);
        bullet->addComponent<Animator>(2, 1, 3.0f, 200, 120, 32, 15, 0, 0);
    } else {
        bullet->addComponent<Position>(x - 20.f , y + 15.f);
        bullet->addComponent<Rotation>(180.f);
        bullet->addComponent<Velocity>(-10.f, 0.f);
    }
    bullet->addComponent<Sprite>(std::string("../sprites/r-typesheet1.gif"));
    bullet->addComponent<Scale>(2.f);
    bullet->addComponent<Scene>(1);
    bullet->addComponent<Tag>("bullet");
}

/**
 * @brief Creates the loading screen entities.
 *
 * This function initializes the loading screen with text and a progress bar.
 */
void Creator::createLoadingScreen()
{
    auto window = _world.getWindow();
    float centerX = window->getSize().x / 2.0f - 200.f;
    float centerY = window->getSize().y / 2.0f;

    auto title = _world.createEntity();
    title->addComponent<Scene>(0);
    title->addComponent<Text>("LOADING...", "../sprites/title.ttf", 40);
    title->addComponent<Position>(centerX - title->getComponent<Text>()->getGlobalBounds().size.x / 2.0f, centerY - 100.f);
    title->addComponent<Layer>(LayerType::UI);

    auto status = _world.createEntity();
    status->addComponent<Scene>(0);
    status->addComponent<Text>("Initializing...", "../sprites/title.ttf", 20);
    status->addComponent<Position>(centerX - status->getComponent<Text>()->getGlobalBounds().size.x / 2.0f, centerY + 60.f);
    status->addComponent<Layer>(LayerType::UI);
    status->getComponent<Text>()->setColor(sf::Color(200, 200, 200));
    status->addComponent<Tag>("loading_status");

    auto bgBar = _world.createEntity();
    bgBar->addComponent<Scene>(0);
    bgBar->addComponent<Position>(centerX - 200.f, centerY);
    bgBar->addComponent<Sprite>("../sprites/Elements-01.png");
    bgBar->getComponent<Sprite>()->getSprite()->setTextureRect(sf::IntRect({0, 0}, {1, 1}));
    bgBar->addComponent<Scale>(400.f);
    bgBar->getComponent<Sprite>()->getSprite()->setScale({400.f, 20.f}); 
    bgBar->getComponent<Sprite>()->getSprite()->setColor(sf::Color(50, 50, 50));
    bgBar->addComponent<Layer>(LayerType::UI);

    auto fillBar = _world.createEntity();
    fillBar->addComponent<Scene>(0);
    fillBar->addComponent<Position>(centerX - 200.f, centerY);
    fillBar->addComponent<Sprite>("../sprites/Elements-01.png");
    fillBar->getComponent<Sprite>()->getSprite()->setTextureRect(sf::IntRect({0, 0}, {1, 1}));
    fillBar->getComponent<Sprite>()->getSprite()->setScale({0.f, 20.f});
    fillBar->getComponent<Sprite>()->getSprite()->setColor(sf::Color(100, 250, 50));
    
    fillBar->addComponent<Layer>(LayerType::UI + 1);
    fillBar->addComponent<Tag>("loading_bar");
    fillBar->addComponent<Scale>(0.f); 
}
