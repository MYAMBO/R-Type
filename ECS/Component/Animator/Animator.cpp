/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Animator
*/

#include "Animator.hpp"

#include <iostream>


/**
     * @brief Construct a new Animator component.
     *
     * @param nbFrame     Number of frames in the animation.
     * @param framePerRow  Total frames on a Row.
     * @param frameRate   Time (in seconds) between two frames.
     * @param startX      X position of the first frame in the sprite sheet.
     * @param startY      Y position of the first frame in the sprite sheet.
     * @param frameWidth  Width of a single animation frame.
     * @param frameHeight Height of a single animation frame.
     * @param offsetX    Horizontal spacing between frames (default: 0).
     * @param offsetY    Vertical spacing between frames (default: 0).
*/
Animator::Animator(const int nbFrame, const int framePerRow, const float frameRate,
    const int startX, const int startY, const int frameWidth,
    const int frameHeight, const int offsetX, const int offsetY)
    :   _startX(startX), _startY(startY),
        _offsetX(offsetX), _offsetY(offsetY), _frameWidth(frameWidth), _framePerRow(framePerRow),
        _frameHeight(frameHeight), _nbFrame(nbFrame), _frameRate(frameRate),
        _currentFrame(0), _currentTime(0.f)
{
    if (nbFrame <= 0) {
        _nbFrame = 1;
        std::cerr << "Warning: nbFrame value is <= 0, set it at 1 by default" << std::endl;
    }
    if (framePerRow <= 0) {
        _framePerRow = 1;
        std::cerr << "Warning: framePerRow value is <= 0, set it at 1 by default" << std::endl;
    }
}

/**
     * @brief Get the texture rectangle corresponding to the current frame.
     *
     * This rectangle can be assigned directly to a sf::Sprite.
     *
     * @return sf::IntRect representing the current animation frame.
*/
sf::IntRect Animator::getFrameRect() const
{
    int column = _currentFrame % _framePerRow;
    int row = _currentFrame / _framePerRow;

    int x = _startX + row * (_frameWidth + _offsetX);
    int y = _startY + column * (_frameHeight + _offsetY);
    return {
            sf::Vector2i(x, y),
            sf::Vector2i(_frameWidth, _frameHeight)
    };
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
void Animator::setCurrentFrame(const int frame)
{
    _currentFrame = frame % _nbFrame;
}

/**
   * @brief Set a new frame rate.
   *
   * @param frameRate New frame rate in seconds.
*/
void Animator::setFrameRate(const float frameRate)
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


