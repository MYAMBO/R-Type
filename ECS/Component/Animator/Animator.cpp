/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Animator
*/

#include <stdexcept>

#include "Animator.hpp"

Animator::Animator(int nbFrame, float frameRate,
    int startX, int startY, int frameWidth, int frameHeight,
    int offsetX, int offsetY)
    :   _nbFrame(nbFrame), _frameRate(frameRate),
        _startX(startX), _startY(startY), _frameWidth(frameWidth),
        _frameHeight(frameHeight), _offsetX(offsetX), _offsetY(offsetY),
        _currentFrame(0), _currentTime(0.f)
{
}

sf::IntRect Animator::getFrameRect() const
{
    return sf::IntRect(
            sf::Vector2i(
                    _startX + _currentFrame * _offsetX,
                    _startY + _currentFrame * _offsetY),
            sf::Vector2i(_frameWidth, _frameHeight)
    );
}

int Animator::getCurrentFrame() const
{
    return _currentFrame;
}

float Animator::getFrameRate() const
{
    return _frameRate;
}

float Animator::getCurrentTime() const
{
    return _currentTime;
}

void Animator::setCurrentFrame(int frame)
{
    _currentFrame = frame % _nbFrame;
}

void Animator::setFrameRate(float frameRate)
{
    _frameRate = frameRate;
}

void Animator::setCurrentTime(const float currentTime)
{
    _currentTime = currentTime;
}


