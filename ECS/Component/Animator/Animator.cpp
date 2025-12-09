/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Animator
*/

#include "Animator.hpp"


/**
     * @brief Construct a new Animator component.
     *
     * @param nbFrame     Number of frames in the animation.
     * @param frameRate   Time (in seconds) between two frames.
     * @param startX      X position of the first frame in the sprite sheet.
     * @param startY      Y position of the first frame in the sprite sheet.
     * @param frameWidth  Width of a single animation frame.
     * @param frameHeight Height of a single animation frame.
     * @param offsetX    Horizontal spacing between frames (default: 0).
     * @param offsetY    Vertical spacing between frames (default: 0).
*/
Animator::Animator(int nbFrame, float frameRate,
    int startX, int startY, int frameWidth, int frameHeight,
    int offsetX, int offsetY)
    :   _nbFrame(nbFrame), _frameRate(frameRate),
        _startX(startX), _startY(startY), _frameWidth(frameWidth),
        _frameHeight(frameHeight), _offsetX(offsetX), _offsetY(offsetY),
        _currentFrame(0), _currentTime(0.f)
{
}

/**
     * @brief Get the texture rectangle corresponding to the current frame.
     *
     * This rectangle can be assigned directly to an sf::Sprite.
     *
     * @return sf::IntRect representing the current animation frame.
*/
sf::IntRect Animator::getFrameRect() const
{
    return sf::IntRect(
            sf::Vector2i(
                    _startX + _currentFrame * _offsetX,
                    _startY + _currentFrame * _offsetY),
            sf::Vector2i(_frameWidth, _frameHeight)
    );
}

/**
    * @brief Get the current animation frame index.
    *
    * @return Current frame index.
*/
int Animator::getCurrentFrame() const
{
    return _currentFrame;
}


/**
    * @brief Get the frame rate of the animation.
    *
    * @return Frame rate in seconds.
*/
float Animator::getFrameRate() const
{
    return _frameRate;
}

/**
    * @brief Get the current elapsed time since the last frame change.
    *
    * @return Current accumulated time.
*/
float Animator::getCurrentTime() const
{
    return _currentTime;
}

/**
 * @brief Set the current animation frame.
 *
 * @param frame Frame index to set.
*/
void Animator::setCurrentFrame(int frame)
{
    _currentFrame = frame % _nbFrame;
}

/**
   * @brief Set a new frame rate.
   *
   * @param frameRate New frame rate in seconds.
*/
void Animator::setFrameRate(float frameRate)
{
    _frameRate = frameRate;
}

/**
     * @brief Set the current animation time.
     *
     * @param currentTime Time accumulator value.
*/
void Animator::setCurrentTime(const float currentTime)
{
    _currentTime = currentTime;
}


