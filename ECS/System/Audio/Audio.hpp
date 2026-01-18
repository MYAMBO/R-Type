/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Audio System
*/

#ifndef AUDIO_HPP_
    #define AUDIO_HPP_

    #include "World.hpp"

/**
 * @brief Audio system responsible for updating Audio components.
 * It handles PLAYING, PAUSED, and STOPPED states for every Audio component.
 * PLAYING triggers a sound playback in a detached thread so sounds do not cut each other.
 */
class Audio : public System {
    public:
        Audio() = default;
        ~Audio() override = default;

        void update(const float &dt, World &w) override;
};

#endif /* !AUDIO_HPP_ */
