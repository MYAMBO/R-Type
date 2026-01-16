/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** SoundEffect Component
*/

#include <thread>
#include <iostream>

#include "SoundEffect.hpp"

/**
 * @brief Construct a new SoundEffect component.
 * @param filePath Path to the SoundEffect file
 * @param volume Initial volume (0 to 100)
*/
SoundEffect::SoundEffect(const std::string& filePath, float volume)
    : _buffer(std::make_shared<sf::SoundBuffer>()),
      _sound(*_buffer)
{
    if (!_buffer->loadFromFile(filePath)) {
        std::cerr << "[SoundEffect] Failed to load: " << filePath << "\n";
        return;
    }
    _sound.setVolume(volume);
    _state = AudioState::STOPPED;
}


/**
 * @brief Play the sound.
*/
void SoundEffect::play()
{
    _state = AudioState::PLAYING;
}

/**
 * @brief Set the volume of the sound.
 * @param volume Volume level (0 to 100)
*/
void SoundEffect::setVolume(float volume)
{
    _sound.setVolume(volume);
}

/**
 * @brief Set the pitch of the sound.
 * @param pitch Pitch level (1.0 is normal)
*/
void SoundEffect::setPitch(float pitch)
{
    _sound.setPitch(pitch);
}

/**
 * @brief Get the current volume of the sound.
 * @return float Current volume level
*/
float SoundEffect::getVolume() const
{
    return _sound.getVolume();
}

/**
 * @brief Get the current pitch of the sound.
 * @return float Current pitch level
*/
float SoundEffect::getPitch() const
{
    return _sound.getPitch();
}

/**
 * @brief Get the current status of the sound (Playing, Paused, Stopped).
 * @return sf::Sound::Status Current sound status
*/
 AudioState SoundEffect::getStatus() const
{
    return _state;
}

/**
 * @brief Set the current status of the sound.
 * @param state New sound status
*/
void SoundEffect::setStatus( AudioState state)
{
    _state = state;
}

/**
 * @brief Get the sound buffer.
 * @return std::shared_ptr<sf::SoundBuffer> Shared pointer to the sound buffer
*/
std::shared_ptr<sf::SoundBuffer> SoundEffect::getBuffer() const
{
    return _buffer;
}

/**
 * @brief Set whether the sound is global (not affected by scene changes).
 * @param global True if global, false otherwise
*/
void SoundEffect::setGlobal(bool global)
{
    _global = global;
}

/**
 * @brief Check if the sound is global.
 * @return bool True if global, false otherwise
*/
bool SoundEffect::isGlobal() const
{
    return _global;
}

/**
 * @brief Get the current SFML sound status.
 * @return sf::Sound::Status Current SFML sound status
*/
sf::Sound::Status SoundEffect::getSfStatus() const
{
    return _sound.getStatus();
}