/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Animator
*/

#ifndef R_TYPE_ANIMATOR_HPP
    #define R_TYPE_ANIMATOR_HPP

#include <memory>
#include <SFML/Graphics/Rect.hpp>

#include "Component.hpp"


/**
 * @brief Animator component to animate the sprite of entities.
 *
 * The Animator component handles frame-based animations by selecting
 * sub-rectangles from a texture atlas (sprite sheet).
 * It manages timing, frame switching, and texture offsets.
*/
class Animator : public Component {
public:

    Animator(int nbFrame, float frameRate,
             int startX, int startY, int frameWidth, int frameHeight,
             int offsetX = 0, int offsetY = 0);
    virtual ~Animator() = default;

    [[nodiscard]] int getCurrentFrame() const;
    [[nodiscard]] float getFrameRate() const;
    [[nodiscard]] float getCurrentTime() const;
    [[nodiscard]] sf::IntRect getFrameRect() const;

    void setFrameRate(const float frameRate);
    void setCurrentFrame(const int currentFrame);
    void setCurrentTime(const float currentTime);

private:
    int _startX;
    int _startY;
    int _offsetX;
    int _offsetY;
    int _frameWidth;
    int _frameHeight;
    int _nbFrame;
    float _frameRate;
    int _currentFrame;
    float _currentTime;
};

#endif //R_TYPE_ANIMATOR_HPP
