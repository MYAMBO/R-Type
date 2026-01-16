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
        {"death_sound", "../assets/sounds/killed_first.mp3"}
    });
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
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
        {"death_sound", "../assets/sounds/killed_second.mp3"}
    });
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
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
        {"death_sound", "../assets/sounds/killed_first.mp3"}
    });
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
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
        {"death_sound", "../assets/sounds/killed_second.mp3"}
    });
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
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
        {"death_sound", "../assets/sounds/killed_second.mp3"}
    });
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
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
    soundEntity->addComponent<Tag>("sound_effect");
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