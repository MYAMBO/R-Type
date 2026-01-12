/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** Music Component
*/

#include "Music.hpp"
#include <iostream>

/**
 * @brief Construct a new Music component.
 * @param filePath Path to the Music file
 * @param volume Initial volume (0 to 100)
 * @param loop Whether the music should loop
*/
Music::Music(const std::string& filePath, float volume, bool loop)
    : _targetState(MusicState::STOPPED)
{
    if (!_music.openFromFile(filePath)) {
        std::cerr << "[Music] Error opening music file: " << filePath << std::endl;
    }
    _music.setVolume(volume);
    _music.setLooping(loop);
}

/**
 * @brief Play the music.
*/
void Music::play()
{
    _targetState = MusicState::PLAYING;
}

/**
 * @brief Pause the music.
*/
void Music::pause()
{
    _targetState = MusicState::PAUSED;
}

/**
 * @brief Stop the music.
*/
void Music::stop()
{
    _targetState = MusicState::STOPPED;
}

/**
 * @brief Set the volume of the music.
 * @param volume Volume level (0 to 100)
*/
void Music::setVolume(float volume)
{ 
    _music.setVolume(volume);
}

/**
 * @brief Set whether the music should loop.
 * @param loop True to enable looping, false to disable
*/
void Music::setLoop(bool loop)
{ 
    _music.setLooping(loop);
}

/**
 * @brief Set the pitch of the music.
 * @param pitch Pitch level (1.0 is normal)
*/
void Music::setPitch(float pitch)
{ 
    _music.setPitch(pitch);
}

/**
 * @brief Get the current volume of the music.
 * @return float Current volume level
*/
float Music::getVolume() const
{ 
    return _music.getVolume();
}

/**
 * @brief Check if the music is set to loop.
 * @return bool True if looping is enabled, false otherwise
*/
bool Music::isLooping() const
{ 
    return _music.isLooping();
}

/**
 * @brief Get the current target state of the music (Playing, Paused, Stopped).
 * @return MusicState Current music state
*/
MusicState Music::getState() const
{ 
    return _targetState;
}