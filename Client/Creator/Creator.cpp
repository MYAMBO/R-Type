/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Creator
*/

#include "Creator.hpp"
#include "GameHelper.hpp"

#include "Tag.hpp"
#include "Position.hpp"
#include "Sprite.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Button.hpp"
#include "Text.hpp"
#include "Script.hpp"
#include "HP.hpp"
#include "Velocity.hpp"
#include "Animator.hpp"
#include "Rotation.hpp"
#include "Layer.hpp"
#include "Group.hpp"
#include "BoxCollider.hpp"
#include "Game.hpp"
#include "ScriptsHandler.hpp"

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
    btnEntity->addComponent<Scale>(0.25f);
    btnEntity->addComponent<Scene>(sceneId);
    btnEntity->addComponent<Layer>(LayerType::UI);
    
    float width = (1200.f * 0.25f);
    float height = (500.f * 0.25f);
    
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
    unsigned int width = (window) ? window->getSize().x : 1920;
    float centerX = static_cast<float>(width) / 2.0f;
    float btnX = centerX;

    auto titleEntity = _world.createEntity();
    titleEntity->addComponent<Scene>(2);
    titleEntity->addComponent<Layer>(LayerType::UI);
    titleEntity->addComponent<Text>("R-TYPE", "../sprites/title.ttf", 80);
    titleEntity->addComponent<Position>(centerX - 150.f, 100.f); // Centrage approximatif titre
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

/**
 * @brief Create Options (Scene 3)
 */
void Creator::createOptions()
{
    auto window = _world.getWindow();
    unsigned int width = (window) ? window->getSize().x : 1920;
    float centerX = static_cast<float>(width) / 2.0f;
    float btnX = centerX;

    auto titleEntity = _world.createEntity();
    titleEntity->addComponent<Scene>(3); // Scene 3
    titleEntity->addComponent<Layer>(LayerType::UI);
    titleEntity->addComponent<Text>("OPTIONS", "../sprites/title.ttf", 80);
    titleEntity->addComponent<Position>(centerX - 180.f, 50.f);
    titleEntity->getComponent<Text>()->setColor(sf::Color::Green);

    static bool godMode = false;
    static bool colorBlind = false;
    createMenuButton("GOD MODE", 3, btnX, 200.f, []() {
        godMode = !godMode;
        std::cout << "God Mode: " << (godMode ? "ON" : "OFF") << std::endl;
    });

    createMenuButton("EASY MODE", 3, btnX, 325.f, []() {
        std::cout << "Difficulty set to: EASY" << std::endl;
    });

    createMenuButton("HARD MODE", 3, btnX, 450.f, []() {
        std::cout << "Difficulty set to: HARD" << std::endl;
    });

    createMenuButton("DALTONIAN", 3, btnX, 575.f, []() {
        colorBlind = !colorBlind;
        std::cout << "Colorblind Mode: " << (colorBlind ? "ON" : "OFF") << std::endl;
    });

    createMenuButton("RETURN", 3, btnX, 750.f, [this]() {
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
    player->addComponent<BoxCollider>(33.0f, 19.0f);

    if (playerCount == 0) {
        // Premier joueur (joueur local)
        player->addComponent<Velocity>(0.f, 0.f);
        player->addComponent<Animator>(2, 1, 3.f, 0, 0, 33, 19, 0, 0);
        player->addComponent<Tag>("player");
    } else {
        // Autres joueurs (coéquipiers)
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
