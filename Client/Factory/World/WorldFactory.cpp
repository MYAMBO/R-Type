/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** WorldFactory
*/

#include "Game.hpp"
#include "Factory.hpp"
#include "Collision.hpp"
#include "WorldFactory.hpp"

#include <thread>
static int playerCount = 0;


WorldFactory::WorldFactory(World& world) : _world(world)
{
}

void WorldFactory::createMusicGameplay()
{
    auto music = _world.createEntity();
    music->addComponent<Music>("../assets/sounds/game.mp3", 50.f, true);
    music->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    music->addComponent<Tag>("gameplay_music");
    music->addComponent<Script>([](int entityId, World& world) {
        if (world.getCurrentScene() != static_cast<int>(SceneType::GAMEPLAY)) {
            if (auto entity = GameHelper::getEntityById(world, entityId)) {
                auto musicComp = entity->getComponent<Music>();
                if (musicComp && musicComp->getState() == MusicState::PLAYING) {
                    musicComp->stop();
                }
            }
            return;
        }
        auto entity = GameHelper::getEntityById(world, entityId);
        if (!entity)
            return;
        auto musicComp = entity->getComponent<Music>();
        if (musicComp && musicComp->getState() != MusicState::PLAYING) {
            musicComp->play();
        }
    });
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
        bullet->addComponent<Animator>(2, 2, 3.0f, 200, 120, 32, 15, 0, 0);
        bullet->addComponent<HP>(10);
        bullet->addComponent<Damage>(10);
        bullet->addComponent<BoxCollider>(32.0f, 15.0f);
    } else {
        bullet->addComponent<Position>(x - 20.f , y + 15.f);
        bullet->addComponent<Rotation>(180.f);
        //bullet->addComponent<Velocity>(-10.f, 0.f);
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
        SHOOTING,
        PORTALBOSS,
        PORTAL
    };
    switch (type) {
        case BASIC:
            GameHelperGraphical::createBasicEnemy(_world, x, y, entityId);
            break;
        case FAST:
            GameHelperGraphical::createFastEnemy(_world, x, y, entityId);
            break;
        case TANK:
            GameHelperGraphical::createTankEnemy(_world, x, y, entityId);
            break;
        case SINUS:
            GameHelperGraphical::createSinusEnemy(_world, x, y, entityId);
            break;
        case SHOOTING:
            GameHelperGraphical::createShootingEnemy(_world, x, y, entityId);
            break;
        case PORTALBOSS:
            GameHelperGraphical::createPortalBoss(_world, x, y, entityId);
            break;
        case PORTAL:
            GameHelperGraphical::createWarningPortal(_world, x, y, entityId);
            break;
        default:
            std::cerr << "Unknown enemy type: " << type << std::endl;
            break;
    }
}

void WorldFactory::createPowerUp(float x, float y, int type, int entityId)
{
    enum EnemyType {
        HEAL = 1,
        SPEED,
        HOMING
    };
    switch (type) {
    case HEAL:
        GameHelperGraphical::createHealPowerUp(_world, x, y, entityId);
        break;
    default:
        std::cerr << "Unknown power up type: " << type << std::endl;
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

void WorldFactory::createBackwardEnemyBullet(size_t entityId, int x, int y)
{
    auto entity = GameHelper::getEntityById(_world, entityId);
    if (entity)
        return;
    auto bullet = _world.createEntity(entityId);
    bullet->addComponent<Position>(x, y);
    bullet->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet1.gif"));
    bullet->addComponent<Animator>(4, 4, 3.0f, 206, 273, 17, 17, 0, 0);
    bullet->addComponent<Scale>(2.f);
    bullet->addComponent<Scene>(1);
    bullet->addComponent<HP>(10);
    bullet->addComponent<Damage>(10);
    bullet->addComponent<BoxCollider>(32.0f, 15.0f);
    bullet->addComponent<Tag>("enemy_bullet");
}

/**
 * @brief Creates the player entity.
 * 
 * This function initializes the player entity with necessary components.
 */
void WorldFactory::createPlayer(uint64_t id, float x, float y)
{
    if (GameHelper::getEntityById(_world, id) != nullptr)
        return;
    if (playerCount >= 4)
        return;
    playerCount++;
    auto player = _world.createEntity(id);
    player->addComponent<HP>(100);
    player->addComponent<Position>(x, y);
    player->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet42.gif"));
    player->addComponent<Scale>(3.f);
    player->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    player->addComponent<SoundEffect>(std::string("../assets/sounds/lazershoot.mp3"));
    player->addComponent<Layer>(10);
    player->addComponent<Group>(playerCount);
    player->addComponent<Damage>(10);
    player->addComponent<BoxCollider>(33.0f, 19.0f);

    std::map<std::string, std::string> dataMap = {
        {"mana", "100"},
        {"scraps", "0"},
        {"died", "false"}
    };
    player->addComponent<Data>(dataMap);

    if (playerCount - 1 == 0) {
        player->addComponent<Velocity>(0.f, 0.f);
        player->addComponent<Animator>(2, 2, 3.f, 0, 0, 33, 19, 0, 0);
        player->addComponent<Tag>("player");
    } else {
        player->addComponent<Animator>(2, 2, 3.f, 0, ((playerCount - 1) * 17), 33, 19, 0, 0);
        player->addComponent<Tag>("player_mate");
    }

    auto fire = _world.createEntity();
    fire->addComponent<Position>(0.f, 85.f);
    fire->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet1.gif"));
    fire->addComponent<Animator>(2, 1, 3.f, 285, 85, 15, 15, 0, 0);
    fire->addComponent<Scale>(3.f);
    fire->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    fire->addComponent<Script>(playerfire);
    fire->addComponent<Group>(playerCount);
    fire->addComponent<Layer>(10);
    fire->addComponent<Tag>("fire");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

/**
 * @brief Creates a companion entity that orbits around the player.
 * 
 * This function initializes a companion entity with necessary components.
 * @param playerId The ID of the player entity to which the companion will be linked.
 */
void WorldFactory::createCompanion(uint64_t playerId)
{
    auto player = GameHelper::getEntityById(_world, playerId);
    if (!player) {
        std::cerr << "Player entity not found for companion creation." << std::endl;
        return;
    }
    auto companion = _world.createEntity();
    companion->addComponent<Position>(player->getComponent<Position>()->getX() + 20.f,
                                     player->getComponent<Position>()->getY() - 50.f);
    companion->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet2.gif"));
    companion->addComponent<Scale>(1.5f);
    companion->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    companion->addComponent<Layer>(LayerType::UI + 1);
    companion->addComponent<Tag>("companion");
    companion->addComponent<Animator>(5, 5, 3.f, 158, 35, 21, 16, 3, 3);
    companion->addComponent<Group>(player->getComponent<Group>()->getId());
    companion->addComponent<Data>(std::map<std::string, std::string>{{"orbit_angle", "0.0"}, {"level", "0"}, {"changed", "false"}});
    companion->addComponent<SoundEffect>(std::string("../assets/sounds/create2.mp3"), 100.f);
    companion->getComponent<SoundEffect>()->play();
    companion->addComponent<Script>(companionScript);
}

void WorldFactory::createLasersCompanion(uint64_t companionId, uint64_t playerId)
{
    auto companion = GameHelper::getEntityById(_world, companionId);
    auto player = GameHelper::getEntityById(_world, playerId);
    if (!companion || !player) {
        std::cerr << "Companion or Player entity not found for laser creation." << std::endl;
        return;
    }
    auto laser = _world.createEntity();
    laser->addComponent<Position>(companion->getComponent<Position>()->getX() + 10.f,
                                 companion->getComponent<Position>()->getY() + 30.f);
    laser->addComponent<Sprite>("../assets/sprites/fire_effect.png");
    laser->addComponent<Animator>(2, 2, 1.f, 223, 0, 16, 16, 0, 0);
    laser->addComponent<Rotation>(270.f);
    laser->addComponent<Scale>(3.f);
    laser->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    laser->addComponent<Velocity>(9.f, 0.f);
    laser->addComponent<Layer>(10);
    laser->addComponent<Tag>("companion_laser");
    laser->addComponent<Group>(companion->getComponent<Group>()->getId());
    laser->addComponent<SoundEffect>(std::string("../assets/sounds/miniLaser.mp3"), 100.f);
    laser->addComponent<Script>(companionLaserScript);
    laser->getComponent<SoundEffect>()->play();
}

void WorldFactory::createScraps(World &world, float x, float y)
{
    auto scrap = world.createEntity();
    scrap->addComponent<Position>(x, y);
    scrap->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    scrap->addComponent<Layer>(5);
    scrap->addComponent<Sprite>("../assets/sprites/r-typesheet3.gif");
    scrap->getComponent<Sprite>()->getSprite()->setTextureRect(sf::IntRect({0, 0}, {16, 16}));
    scrap->getComponent<Sprite>()->getSprite()->setOrigin({scrap->getComponent<Sprite>()->getSprite()->getGlobalBounds().size.x / 2,
                                                            scrap->getComponent<Sprite>()->getSprite()->getGlobalBounds().size.y / 2});
    scrap->addComponent<Animator>(1, 1, 1.f, 0, 0, 16, 16, 0, 0);
    scrap->addComponent<Scale>(3.0f);
    scrap->addComponent<Tag>("scrap");
    scrap->addComponent<BoxCollider>(42.f, 42.f);
    scrap->getComponent<BoxCollider>()->setOffset(-42.f, -42.f);
    scrap->addComponent<Rotation>(0.f);
    scrap->addComponent<SoundEffect>("../assets/sounds/pickup.mp3", 100.f);

    scrap->addComponent<Script>([this](int entityId, World& w) {
        if (w.getCurrentScene() != static_cast<int>(SceneType::GAMEPLAY))
            return;
        auto sEnt = GameHelper::getEntityById(w, entityId);
        auto pEnt = GameHelper::getEntityByTag(w, "player");
        if (!sEnt || !pEnt)
            return;

        auto sCol = sEnt->getComponent<BoxCollider>();
        auto sPos = sEnt->getComponent<Position>();
        auto pCol = pEnt->getComponent<BoxCollider>();
        auto pPos = pEnt->getComponent<Position>();
        if (!sCol || !sPos || !pCol || !pPos)
            return;

        sPos->setY(sPos->getY() + 1.f);
        sPos->setX(sPos->getX() - 0.5f);
        if (auto rot = sEnt->getComponent<Rotation>())
            rot->setRotation(rot->getRotation() + 5.f);

        if (Collision::checkCollision(*sCol, *sPos, *pCol, *pPos)) {
            if (auto pSfx = pEnt->getComponent<SoundEffect>())
                pSfx->play();
            auto companion = GameHelper::getEntityByTag(w, "companion");
            if (companion)
                if (auto cData = companion->getComponent<Data>())
                    if (cData->getData("level") == "4") {
                        w.killEntity(entityId);
                        return;
                    }
            auto pData = pEnt->getComponent<Data>();
            int count = std::stoi(pData->getData("scraps")) + 1;
            if (count <= 3) {
                pData->setData("scraps", std::to_string(count));
                this->createScrapUI(w, count);
            } 
            else {
                pData->setData("scraps", "0");
                auto companion = GameHelper::getEntityByTag(w, "companion");
                if (!companion) {
                    this->createCompanion(pEnt->getId());
                } else {
                    auto cData = companion->getComponent<Data>();
                    if (cData) {
                        int currentLvl = std::stoi(cData->getData("level"));
                        if (currentLvl >= 4) {
                            w.killEntity(entityId);
                            return;
                        }
                        if (currentLvl < 4)
                            cData->setData("level", std::to_string(currentLvl + 1));
                        cData->setData("changed", "false");
                    }
                    if (cData->getData("level") != "4") {
                        for (int i = 1; i <= 3; i++) {
                            auto uiIcon = GameHelper::getEntityByTag(w, "ui_scrap_icon_" + std::to_string(i));
                            if (uiIcon)
                                w.killEntity(uiIcon->getId());
                        }
                    }
                    w.killEntity(entityId);
                    return;
                }
                for (int i = 1; i <= 3; i++) {
                    auto uiIcon = GameHelper::getEntityByTag(w, "ui_scrap_icon_" + std::to_string(i));
                    if (uiIcon)
                        w.killEntity(uiIcon->getId());
                }
            }
            w.killEntity(entityId);
        }
    });
}

/**
 * @brief Create Scrap UI Element
 * This function initializes a scrap UI element entity with necessary components.
*/
void WorldFactory::createScrapUI(World &world, int index)
{
    float posX = 40.f + (index - 1) * 30.f;
    float posY = 110.f; 

    auto uiScrap = world.createEntity();
    uiScrap->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    uiScrap->addComponent<Layer>(LayerType::UI + 3);
    uiScrap->addComponent<Position>(posX, posY);
    uiScrap->addComponent<Sprite>("../assets/sprites/r-typesheet3.gif");
    uiScrap->addComponent<Animator>(1, 1, 1.f, 0, 0, 16, 16, 0, 0);
    uiScrap->addComponent<Scale>(2.f);
    uiScrap->addComponent<Tag>("ui_scrap_icon_" + std::to_string(index));
    uiScrap->addComponent<Script>([](int entityId, World& world) {
        if (world.getCurrentScene() != static_cast<int>(SceneType::GAMEPLAY))
            return;
        auto player = GameHelper::getEntityByTag(world, "player");
        auto uiScrap = GameHelper::getEntityById(world, entityId);
        if (!player || !uiScrap)
            return;
        auto group = player->getComponent<Group>();
        if (!group)
            return;
        auto groupEntities = GameHelper::getEntitiesByGroup(world, group->getId());
        for (auto& ent : groupEntities) {
            if (ent->getComponent<Tag>()->getTag() == "companion") {
                auto companionData = ent->getComponent<Data>();
                if (companionData) {
                    int currentLvl = std::stoi(companionData->getData("level"));
                    if (currentLvl == 4)
                        uiScrap->getComponent<Sprite>()->getSprite()->setColor(sf::Color(255, 215, 0, 255));
                }
                break;
            }
        }
    });
}