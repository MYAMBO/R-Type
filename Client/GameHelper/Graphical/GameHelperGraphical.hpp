/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** GameHelperGraphical
*/

#ifndef GAMEHELPERGRAPHICAL_HPP_
    #define GAMEHELPERGRAPHICAL_HPP_

    #include <map>
    #include <memory>

    #include "World.hpp"
    #include "GameHelper.hpp"

/**
* @brief Enumeration for different color blindness modes.
*/
enum class ColorBlindMode {
    Normal = 0,
    Protanopia,
    Deuteranopia,
    Tritanopia,
    Achromatopsia
};

/**
 * @brief Structure representing a color transformation matrix.
*/
struct ColorMatrix {
    float r[3];
    float g[3];
    float b[3];
};

/**
* @brief Predefined color matrices for different color blindness modes.
*/
const std::map<ColorBlindMode, ColorMatrix> ColorFilters = {
    {ColorBlindMode::Protanopia,   {{0.567f, 0.433f, 0.0f}, {0.558f, 0.442f, 0.0f}, {0.0f, 0.242f, 0.758f}}},
    {ColorBlindMode::Deuteranopia, {{0.625f, 0.375f, 0.0f}, {0.70f, 0.30f, 0.0f}, {0.0f, 0.30f, 0.70f}}},
    {ColorBlindMode::Tritanopia,   {{0.95f, 0.05f, 0.0f}, {0.0f, 0.433f, 0.567f}, {0.0f, 0.475f, 0.525f}}},
    {ColorBlindMode::Achromatopsia,{{0.299f, 0.587f, 0.114f}, {0.299f, 0.587f, 0.114f}, {0.299f, 0.587f, 0.114f}}}
};

class GameHelperGraphical {
    public:
        GameHelperGraphical() = delete;
        ~GameHelperGraphical() = delete;

        static sf::Color hueToRGB(float hue);
        static ColorMatrix getColorMatrix(ColorBlindMode mode);
        static std::shared_ptr<Camera> getMainCamera(World &world);

        static void createSparks(World &world, float x, float y, int amount);
        static void createTankEnemy(World &world, float x, float y, int entityId);
        static void createFastEnemy(World &world, float x, float y, int entityId);
        static void createPortalBoss(World &world, float x, float y, int entityId);
        static void createSinusEnemy(World &world, float x, float y, int entityId);
        static void createBasicEnemy(World &world, float x, float y, int entityId);
        static void createShootingEnemy(World &world, float x, float y, int entityId);
        static void createScoreGUI(World &world, float x, float y, const std::string& scoreText);
        static void soundEffectEntity(const std::string& filepath, float volume, int scene, World& world);
        static void createAnimatorEntity(World &world, float x, float y, const std::string& spritePath, int rows,
                int cols, float animSpeed, int startX, int startY, int frameWidth, int frameHeight, int offsetX = 0, int offsetY = 0, float scale = 1.f);
};

#endif /* !GAMEHELPERGRAPHICAL_HPP_ */