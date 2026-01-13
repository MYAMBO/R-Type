/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** WorldFactory
*/

#include "Game.hpp"
#include "Factory.hpp"
#include "WorldFactory.hpp"

WorldFactory::WorldFactory(World& world) : _world(world)
{
}

/**
 * @brief Creates a bullet entity.
 *
 * This function initializes a bullet entity with necessary components.
 * @param entityId The ID of the entity that fired the bullet.
 */
void WorldFactory::createBullet(size_t entityId, int x, int y, int type)
{
    auto entity = GameHelper::getEntityById(_world, entityId);
    if (entity)
        return;
    bool isPlayer = (type == Bullet);
    auto bullet = _world.createEntity(entityId);
    if (isPlayer) {
        bullet->addComponent<Position>(x, y);
        bullet->addComponent<Velocity>(10.f, 0.f);
        bullet->addComponent<Animator>(2, 2, 3.0f, 200, 120, 32, 15, 0, 0);
        bullet->addComponent<HP>(10);
        bullet->addComponent<Damage>(10);
        bullet->addComponent<BoxCollider>(32.0f, 15.0f);
    } else {
        bullet->addComponent<Position>(x - 20.f , y + 15.f);
        bullet->addComponent<Rotation>(180.f);
        bullet->addComponent<Velocity>(-10.f, 0.f);
    }
    bullet->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet1.gif"));
    bullet->addComponent<Scale>(2.f);
    bullet->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    bullet->addComponent<Tag>("player_bullet");
}


/**
 * @brief Create Camera
 * This function initializes a camera entity with necessary components.
*/
void WorldFactory::createCamera()
{
    auto cameraEntity = _world.createEntity();
    cameraEntity->addComponent<Camera>(sf::Vector2f(1920.f, 1080.f), sf::Vector2f(0.f, 0.f));
    cameraEntity->addComponent<Tag>("main_camera");
}

/**
 * @brief Create Enemy
 * This function initializes an enemy entity with necessary components.
*/
void WorldFactory::createEnemy(float x, float y, int type, int entityId)
{
    enum EnemyType {
        BASIC = 1,
        FAST,
        TANK,
        SINUS, 
        SHOOTING
    };
    switch (type) {
        case BASIC:
            GameHelper::createBasicEnemy(_world, x, y, entityId);
            break;
        case FAST:
            // Implement fast enemy creation
            break;
        case TANK:
            // Implement tank enemy creation
            break;
        case SINUS:
            GameHelper::createSinusEnemy(_world, x, y, entityId);
            break;
        case SHOOTING:
            GameHelper::createShootingEnemy(_world, x, y, entityId);
            break;
        default:
            std::cerr << "Unknown enemy type: " << type << std::endl;
            break;
    }
}

/**
 * @brief Create Enemy Bullet
 * This function initializes an enemy bullet entity with necessary components.
*/
void WorldFactory::createEnemyBullet(size_t entityId, int x, int y)
{
    auto entity = GameHelper::getEntityById(_world, entityId);
    if (entity)
        return;
    auto bullet = _world.createEntity(entityId);
    bullet->addComponent<Position>(x, y);
    bullet->addComponent<Rotation>(180.f);
   // bullet->addComponent<Velocity>(-10.f, 0.f);
    bullet->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet1.gif"));
    bullet->addComponent<Animator>(2, 2, 3.0f, 200, 120, 32, 15, 0, 0);
    bullet->addComponent<Scale>(2.f);
    bullet->addComponent<Scene>(1);
    bullet->addComponent<HP>(10);
    bullet->addComponent<Damage>(10);
    bullet->addComponent<BoxCollider>(32.0f, 15.0f);
    bullet->addComponent<Tag>("enemy_bullet");

    auto sprite = bullet->getComponent<Sprite>();
    if (sprite && sprite->getSprite())
        sprite->getSprite()->setColor(sf::Color(255, 150, 50));
}

/**
 * @brief Create Background
 * This function initializes the background entities with necessary components.
*/
void WorldFactory::createBackground(sf::RenderWindow& window)
{
    auto backgroundFirst = _world.createEntity();
    backgroundFirst->addComponent<Sprite>(std::string("../assets/sprites/background.png"));
    
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
    backgroundFirst->addComponent<Velocity>(-5.f, 0.f);
    backgroundFirst->addComponent<Tag>("background_first");
    auto backgroundSecond = _world.createEntity();
    backgroundSecond->addComponent<Sprite>(std::string("../assets/sprites/background.png"));
    backgroundSecond->addComponent<Scale>(1.f);
    backgroundSecond->addComponent<Scene>(_world.getCurrentScene());
    auto bounds = backgroundFirst->getComponent<Sprite>()->getSprite()->getGlobalBounds();
    backgroundSecond->addComponent<Position>(bounds.size.x - 10.f, 0.f);
    backgroundSecond->addComponent<Velocity>(-5.f, 0.f);
    backgroundSecond->addComponent<Script>(backgroundScrollScript);
    backgroundSecond->addComponent<Layer>(LayerType::BACKGROUND);
    backgroundSecond->addComponent<Tag>("background_second");
}

/**
 * @brief Creates the player entity.
 * 
 * This function initializes the player entity with necessary components.
 */
void WorldFactory::createPlayer(uint64_t id)
{
    if (GameHelper::getEntityById(_world, id) != nullptr)
        return;
    static int playerCount = 0;
    if (playerCount >= 4)
        return;
    auto player = _world.createEntity(id);
    player->addComponent<HP>(100);
    player->addComponent<Position>(75.0f, 75.0f);
    player->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet42.gif"));
    player->addComponent<Scale>(3.f);
    player->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    player->addComponent<SoundEffect>(std::string("../assets/sounds/lazershoot.mp3"));
    player->addComponent<Layer>(10);
    player->addComponent<Group>(playerCount + 1);
    player->addComponent<Damage>(10);
    player->addComponent<BoxCollider>(33.0f, 19.0f);

    std::map<std::string, std::string> dataMap = {
        {"mana", "100"}
    };
    player->addComponent<Data>(dataMap);

    if (playerCount == 0) {
        player->addComponent<Velocity>(0.f, 0.f);
        player->addComponent<Animator>(2, 2, 3.f, 0, 0, 33, 19, 0, 0);
        player->addComponent<Tag>("player");
    } else {
        player->addComponent<Animator>(2, 2, 3.f, 0, (playerCount * 17), 33, 19, 0, 0);
        player->addComponent<Tag>("player_mate");
    }
    if (player->getComponent<Tag>()->getTag() == "player_mate")
        return;

    playerCount++;
    auto fire = _world.createEntity();
    fire->addComponent<Position>(0.f, 85.f);
    fire->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet1.gif"));
    fire->addComponent<Animator>(2, 1, 3.f, 285, 85, 15, 15, 0, 0);
    fire->addComponent<Scale>(3.f);
    fire->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    fire->addComponent<Script>(playerfire);
    fire->addComponent<Music>("../assets/sounds/game.mp3", 100.f, true);
    fire->addComponent<Group>(playerCount);
    fire->addComponent<Layer>(10);
    fire->addComponent<Tag>("fire");

    auto hpBarRed = _world.createEntity();
    hpBarRed->addComponent<RectangleShape>(400.f, 20.f, 150, 0, 0, 200);
    hpBarRed->addComponent<Position>(20.f, 20.f + (playerCount - 1) * 30.f);
    hpBarRed->addComponent<Layer>(LayerType::UI);
    hpBarRed->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    hpBarRed->addComponent<Tag>("hp_bar_red_" + std::to_string(playerCount));
    hpBarRed->addComponent<Group>(playerCount);

    auto hpBarGreen = _world.createEntity();
    hpBarGreen->addComponent<RectangleShape>(400.f, 20.f, 0, 200, 0, 200);
    hpBarGreen->addComponent<Position>(21.f, 21.f + (playerCount - 1) * 30.f);
    hpBarGreen->addComponent<Layer>(LayerType::UI + 1);
    hpBarGreen->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    hpBarGreen->addComponent<Tag>("hp_bar_green_" + std::to_string(playerCount));
    hpBarGreen->addComponent<Group>(playerCount);
    hpBarGreen->addComponent<Script>(hpBarScript);

    auto manaBarEmpty = _world.createEntity();
    manaBarEmpty->addComponent<RectangleShape>(400.f, 10.f, 150, 150, 255, 200);
    manaBarEmpty->addComponent<Position>(20.f, 45.f + (playerCount - 1) * 30.f);
    manaBarEmpty->addComponent<Layer>(LayerType::UI);
    manaBarEmpty->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    manaBarEmpty->addComponent<Tag>("mana_bar_empty_" + std::to_string(playerCount));
    manaBarEmpty->addComponent<Group>(playerCount);

    auto manaBar = _world.createEntity();
    manaBar->addComponent<RectangleShape>(400.f, 10.f, 0, 0, 255, 200);
    manaBar->addComponent<Position>(21.f, 46.f + (playerCount - 1) * 30.f);
    manaBar->addComponent<Layer>(LayerType::UI + 1);
    manaBar->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    manaBar->addComponent<Tag>("mana_bar_full_" + std::to_string(playerCount));
    manaBar->addComponent<Group>(playerCount);
    manaBar->addComponent<Script>(manaBarScript);
}

