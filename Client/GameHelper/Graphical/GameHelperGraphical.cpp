/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** G ameHelperGraphicalGraphical
*/

#include "HP.hpp"
#include "Tag.hpp"
#include "Group.hpp"
#include "Scene.hpp"
#include "Scale.hpp"
#include "Damage.hpp"
#include "Camera.hpp"
#include "Sprite.hpp"
#include "Script.hpp"
#include "Position.hpp"
#include "Animator.hpp"
#include "Velocity.hpp"
#include "GameHelper.hpp"
#include "BoxCollider.hpp"
#include "SoundEffect.hpp"

#include "Game.hpp"
#include "GameHelper.hpp"
#include "GameHelperGraphical.hpp"

/**
 * @brief Retrieves the main camera from the world.
 *
 * @param world The world containing entities and components.
 * @return A shared pointer to the main Camera component, or nullptr if not found.
 */
std::shared_ptr<Camera> GameHelperGraphical::getMainCamera(World &world)
{
    for (const auto& entity : world.getAllEntitiesWithComponent<Camera>()) {
        if (!entity)
            continue;
        auto tagComp = entity->getComponent<Tag>();
        if (tagComp && tagComp->getTag() == "main_camera") {
            return entity->getComponent<Camera>();
        }
    }
    return nullptr;
}

/**
 * @brief Creates a basic enemy entity in the world at the specified position.
 *
 * @param world The world to create the enemy in.
 * @param x The x-coordinate of the enemy's position.
 * @param y The y-coordinate of the enemy's position.
*/
void GameHelperGraphical::createBasicEnemy(World &world, float x, float y, int entityId)
{
    auto enemy = world.createEntity(entityId);
    enemy->addComponent<HP>(50);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet11.gif"));
    enemy->addComponent<Animator>(2, 6, 5.0f, 0, 0, 33, 30, 33, 0);
    enemy->addComponent<Scale>(2.f);
    enemy->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    enemy->addComponent<Data>(std::map<std::string, std::string>{
        {"score", "+100"},
        {"type", "basic"},
        {"death_sound", "../assets/sounds/killed_first.mp3"},
        {"sound_cooldown", "1"}
    });
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
    enemy->addComponent<Script>(enemyScript);
}

void GameHelperGraphical::createFastEnemy(World &world, float x, float y, int entityId)
{
    auto enemy = world.createEntity(entityId);
    enemy->addComponent<HP>(50);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet5.gif"));
    enemy->addComponent<Animator>(8, 8, 5.0f, 0, 0, 27, 30, 6, 0);
    enemy->addComponent<Scale>(2.f);
    enemy->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    enemy->addComponent<Data>(std::map<std::string, std::string>{
        {"score", "+150"},
        {"type", "fast"},
        {"death_sound", "../assets/sounds/killed_second.mp3"},
        {"sound_cooldown", "1"}
    });
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
    enemy->addComponent<Script>(enemyScript);
}

void GameHelperGraphical::createTankEnemy(World &world, float x, float y, int entityId)
{
    auto enemy = world.createEntity(entityId);
    enemy->addComponent<HP>(50);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet20.gif"));
    enemy->addComponent<Animator>(3, 3, 5.0f, 16, 0, 33, 33, 0, 0);
    enemy->addComponent<Scale>(2.f);
    enemy->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    enemy->addComponent<Data>(std::map<std::string, std::string>{
        {"score", "+200"},
        {"type", "tank"},
        {"death_sound", "../assets/sounds/killed_first.mp3"},
        {"sound_cooldown", "100"}
    });
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
    enemy->addComponent<Script>(enemyScript);
}

/**
 * @brief Creates a sinusoidal enemy entity in the world at the specified position.
 *
 * @param world The world to create the enemy in.
 * @param x The x-coordinate of the enemy's position.
 * @param y The y-coordinate of the enemy's position.
*/
void GameHelperGraphical::createSinusEnemy(World &world, float x, float y, int entityId)
{
    auto enemy = world.createEntity(entityId);
    enemy->addComponent<HP>(50);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet11.gif"));
    enemy->addComponent<Animator>(2, 6, 5.0f, 0, 0, 33, 30, 33, 0);
    enemy->addComponent<Scale>(2.f);
    enemy->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    enemy->addComponent<Data>(std::map<std::string, std::string>{
        {"score", "+300"},
        {"type", "sinus"},
        {"death_sound", "../assets/sounds/killed_second.mp3"},
        {"sound_cooldown", "300"}
    });
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
    enemy->addComponent<Script>(enemyScript);
}

/**
 * @brief Creates a shooting enemy entity in the world at the specified position.
 *
 * @param world The world to create the enemy in.
 * @param x The x-coordinate of the enemy's position.
 * @param y The y-coordinate of the enemy's position.
*/
void GameHelperGraphical::createShootingEnemy(World &world, float x, float y, int entityId)
{
    auto enemy = world.createEntity(entityId);
    enemy->addComponent<HP>(50);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet11.gif"));
    enemy->addComponent<Animator>(2, 6, 5.0f, 0, 0, 33, 30, 33, 0);
    enemy->addComponent<Scale>(2.f);
    enemy->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    enemy->addComponent<Data>(std::map<std::string, std::string>{
        {"score", "+250"},
        {"type", "shooting"},
        {"death_sound", "../assets/sounds/killed_second.mp3"},
        {"sound_cooldown", "300"}
    });
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
    enemy->addComponent<Script>(enemyScript);
}

void GameHelperGraphical::createHealPowerUp(World &world, float x, float y, int entityId)
{
    auto enemy = world.createEntity(entityId);
    enemy->addComponent<HP>(10);
    enemy->addComponent<Damage>(0);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../assets/sprites/Heal.png"));
    enemy->addComponent<Animator>(5, 5, 5.0f, 97, 215, 230, 200, 48, 0);
    enemy->addComponent<Scale>(0.3f);
    enemy->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    enemy->addComponent<Tag>("heal");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
}

void GameHelperGraphical::createWarningPortal(World &world, float x, float y, int entityId)
{
    auto enemy = world.createEntity(entityId);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet30a.gif"));
    enemy->addComponent<Animator>(3, 3, 5.0f, 0, 0, 33, 33, 0, 0);
    enemy->addComponent<Scale>(2.0f);
    enemy->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    enemy->addComponent<Tag>("portal");

    auto sprite = enemy->getComponent<Sprite>();
    if (sprite && sprite->getSprite())
        sprite->getSprite()->setColor(sf::Color::Red);
}

/**
 * @brief Converts a hue value to an RGB color.
 *
 * @param hue The hue value (0-360).
 * @return The corresponding sf::Color in RGB format.
 */
sf::Color GameHelperGraphical::hueToRGB(float hue)
{
    float s = 1.0f;
    float v = 1.0f;
    int i = static_cast<int>(hue / 60.0f) % 6;
    float f = (hue / 60.0f) - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);
    float r, g, b;
    
    switch (i) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
        default: r = g = b = 0; break;
    }

    return sf::Color(
        static_cast<std::uint8_t>(r * 255), 
        static_cast<std::uint8_t>(g * 255), 
        static_cast<std::uint8_t>(b * 255)
    );
}

/**
 * @brief Retrieves the color transformation matrix for a given color blindness mode.
 *
 * @param mode The color blindness mode.
 * @return A 3x3 color transformation matrix.
 */
ColorMatrix GameHelperGraphical::getColorMatrix(ColorBlindMode mode) {
    switch (mode) {
        case ColorBlindMode::Protanopia:
            return {{0.567f, 0.433f, 0.0f}, {0.558f, 0.442f, 0.0f}, {0.0f, 0.242f, 0.758f}};
        case ColorBlindMode::Deuteranopia:
            return {{0.625f, 0.375f, 0.0f}, {0.70f, 0.30f, 0.0f}, {0.0f, 0.30f, 0.70f}};
        case ColorBlindMode::Tritanopia:
            return {{0.95f, 0.05f, 0.0f}, {0.0f, 0.433f, 0.567f}, {0.0f, 0.475f, 0.525f}};
        case ColorBlindMode::Achromatopsia:
            return {{0.299f, 0.587f, 0.114f}, {0.299f, 0.587f, 0.114f}, {0.299f, 0.587f, 0.114f}};
        default:
            return {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
    }
}

/**
 * @brief Creates a sound effect entity in the world.
 *
 * @param filepath The path to the sound file.
 * @param volume The volume of the sound effect.
 * @param scene The scene in which the sound effect should be played.
 * @param world The world to create the sound effect entity in.
*/
void GameHelperGraphical::soundEffectEntity(const std::string& filepath, float volume, int scene, World& world)
{
    auto soundEntity = world.createEntity();
    soundEntity->addComponent<SoundEffect>(filepath, volume);
    soundEntity->addComponent<Scene>(scene);
    soundEntity->addComponent<Tag>("sound_effect" + std::to_string(soundEntity->getId()));
    soundEntity->getComponent<SoundEffect>()->play();
    soundEntity->addComponent<Script>([](int id, World& w) {
        auto entity = GameHelper::getEntityById(w, id);
        if (!entity)
            return;
        auto soundComp = entity->getComponent<SoundEffect>();
        if (soundComp->getSfStatus() == sf::Sound::Status::Stopped) {
            static int safetyFrames = 5; 
            if (safetyFrames-- <= 0) {
                w.killEntity(id);
            }
        }
    });
}

/**
 * @brief Creates a portal boss enemy entity in the world at the specified position.
 *
 * @param world The world to create the enemy in.
 * @param x The x-coordinate of the enemy's position.
 * @param y The y-coordinate of the enemy's position.
*/
void GameHelperGraphical::createPortalBoss(World &world, float x, float y, int entityId)
{
    auto enemy = world.createEntity(entityId);
    enemy->addComponent<HP>(5000);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet41.gif"));
    enemy->addComponent<Animator>(5, 5, 5.0f, 116, 0, 67, 79, 0, 0);
    enemy->addComponent<Scale>(14.f);
    enemy->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    enemy->addComponent<Data>(std::map<std::string, std::string>{
        {"score", "+10000"},
        {"type", "portal_boss"}
    });
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 600.0f);
}

void GameHelperGraphical::createAnimatorEntity(World &world, float x, float y, const std::string& spritePath,
    int rows, int cols, float animSpeed, int startX, int startY, int frameWidth, int frameHeight, int offsetX, int offsetY, float scale)
{
    auto entity = world.createEntity();
    entity->addComponent<Position>(x, y);
    entity->addComponent<Sprite>(spritePath);
    entity->addComponent<Animator>(rows, cols, animSpeed, startX, startY, frameWidth, frameHeight, offsetX, offsetY);
    entity->addComponent<Scale>(scale);
    entity->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    entity->addComponent<Tag>("animator_entity");
    entity->addComponent<Script>([](int id, World& w) {
        auto entity = GameHelper::getEntityById(w, id);
        if (!entity)
            return;
        auto animatorComp = entity->getComponent<Animator>();
        if (!animatorComp)
            return;
        if (animatorComp->getCurrentFrame() == animatorComp->getTotalFrames() - 1) {
            w.killEntity(id);
        }
    });
}

void GameHelperGraphical::createScoreGUI(World &world, float x, float y, const std::string& scoreText)
{
    auto entity = world.createEntity();
    entity->addComponent<Position>(x, y);
    entity->addComponent<Velocity>(0.f, -0.5f);
    entity->addComponent<Text>(scoreText, "../assets/font/regular.ttf", 50);
    entity->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    entity->addComponent<Layer>(LayerType::UI + 5);
    entity->addComponent<Tag>("score_popup");
    entity->addComponent<Data>(std::map<std::string, std::string>{
        {"lifetime", "30"},
        {"hue", "60.0"} 
    });

    entity->addComponent<Script>([](int id, World& w) {
        auto e = GameHelper::getEntityById(w, id);
        if (!e)
            return;

        auto text = e->getComponent<Text>();
        auto data = e->getComponent<Data>();
        if (!text || !data)
            return;

        int life = std::stoi(data->getData("lifetime"));
        float hue = std::stof(data->getData("hue"));

        if (life > 0) {
            hue += 15.0f;
            if (hue >= 360.0f)
                hue = 0.0f;
            sf::Color rainbowCol = GameHelperGraphical::hueToRGB(hue);
            sf::Color currentCol = text->getSfText().getFillColor();
            int newAlpha = (currentCol.a > 8) ? (currentCol.a - 8) : 0;
            text->setColor(rainbowCol.r, rainbowCol.g, rainbowCol.b, newAlpha);
            data->setData("lifetime", std::to_string(life - 1));
            data->setData("hue", std::to_string(hue));
        } else {
            w.killEntity(id);
        }
    });
}

void GameHelperGraphical::playRandomAmbianceEnemy(World &world)
{
    static std::vector<std::string> sounds = {
        "../assets/sounds/first_moaning.mp3",
        "../assets/sounds/second_moaning.mp3",
        "../assets/sounds/third_moaning.mp3"
    };

    printf("Playing enemy ambiance sound\n");
    int choice = rand() % sounds.size();
    
    auto soundEnt = world.createEntity();
    soundEnt->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    soundEnt->addComponent<SoundEffect>(sounds[choice], 40.f);
    float randomPitch = 0.8f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.2f - 0.8f)));
    auto sfx = soundEnt->getComponent<SoundEffect>();
    sfx->setPitch(randomPitch);
    if (sfx)
        sfx->play();

    soundEnt->addComponent<Script>([](int id, World& w) {
        auto e = GameHelper::getEntityById(w, id);
        if (e && e->getComponent<SoundEffect>()->getSfStatus() == sf::Sound::Status::Stopped) {
            w.killEntity(id);
        }
    });
}

/**
 * @brief Creates a star entity in the world at the specified position.
 */
void GameHelperGraphical::createStar(World &world, float x, float y)
{
    auto star = world.createEntity();
    star->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    star->addComponent<Layer>(LayerType::BACKGROUND);
    star->addComponent<Tag>("background_star");

    float randScale = 0.5f + static_cast<float>(rand() % 15) / 10.f;
    float speed = randScale;

    star->addComponent<Position>(x, y);
    star->addComponent<Velocity>(-speed, 0.f);
    star->addComponent<Scale>(randScale);
    
    int starColor = rand() % 2;
    if (starColor == 0) {
        star->addComponent<Sprite>(std::string("../assets/sprites/water_effect.png"));
    } else {
        star->addComponent<Sprite>(std::string("../assets/sprites/purple_effect.png"));
    }
    int starType = rand() % 7;
    switch (starType) {
        case 0: star->addComponent<Animator>(4, 4, 5.f, 223, 48, 16, 16, 0, 0); break;
        case 1: star->addComponent<Animator>(2, 2, 20.f, 160, 80, 16, 16, 0, 0); break;
        case 2: star->addComponent<Animator>(5, 5, 8.f, 385, 16, 16, 16, 0, 0); break;
        case 3: star->addComponent<Animator>(5, 5, 6.f, 480, 0, 16, 16, 0, 0); break;
        case 4: star->addComponent<Animator>(5, 5, 12.f, 480, 48, 16, 16, 0, 0); break;
        case 5: star->addComponent<Animator>(5, 5, 4.f, 480, 96, 16, 16, 0, 0); break;
        case 6: default: 
                star->addComponent<Animator>(5, 5, 10.f, 480, 112, 16, 16, 0, 0); break;
    }
}

/**
 * @brief Initialise le champ d'étoiles et le générateur
 */
void GameHelperGraphical::createStarField(World &world)
{
    auto window = world.getWindow();
    float width = static_cast<float>(window->getSize().x);
    float height = static_cast<float>(window->getSize().y);

    for (int i = 0; i < 50; i++) {
        GameHelperGraphical::createStar(world, static_cast<float>(rand() % (int)width), static_cast<float>(rand() % (int)height));
    }

    auto spawner = world.createEntity();
    spawner->addComponent<Scene>(static_cast<int>(SceneType::GAMEPLAY));
    spawner->addComponent<Tag>("star_spawner");
    spawner->addComponent<Data>(std::map<std::string, std::string>{{"last_heigt", "0"}, {"last_width", "0"}});
    spawner->getComponent<Data>()->setData("last_width", std::to_string(width));
    spawner->getComponent<Data>()->setData("last_height", std::to_string(height));
    
    spawner->addComponent<Script>([](int id, World& w) {
        auto windowsizeX = w.getWindow()->getSize().x;
        auto windowsizeY = w.getWindow()->getSize().y;
        if (rand() % 5 == 0)
            GameHelperGraphical::createStar(w, windowsizeX + 50.f, static_cast<float>(rand() % (int)windowsizeY));

        auto compData = GameHelper::getEntityById(w, id)->getComponent<Data>();
        if (!compData)
            return;
        if (windowsizeX != std::stof(compData->getData("last_width")) || windowsizeY != std::stof(compData->getData("last_height"))) {
            compData->setData("last_height", std::to_string(windowsizeY));
            compData->setData("last_width", std::to_string(windowsizeX));
            auto allStars = w.getAllEntitiesWithComponent<Tag>();
            int starCount = 0;
            for (auto& s : allStars) {
                if (s->getComponent<Tag>()->getTag() == "background_star") starCount++;
            }
            if (starCount < 150) {
                for (int i = 0; i < 10; i++) { 
                    GameHelperGraphical::createStar(w, 
                        static_cast<float>(rand() % (int)windowsizeX), 
                        static_cast<float>(rand() % (int)windowsizeY)
                    );
                }
            }
        }
        for (const auto& star : w.getAllEntitiesWithComponent<Tag>()) {
            if (!star)
                continue;
            auto tagComp = star->getComponent<Tag>();
            if (tagComp && tagComp->getTag() == "background_star") {
                auto posComp = star->getComponent<Position>();
                if (posComp && posComp->getX() < -40.f) {
                    w.killEntity(star->getId());
                }
            }
        }
    });
}