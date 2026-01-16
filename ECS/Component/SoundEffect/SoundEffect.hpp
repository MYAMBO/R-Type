/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** SoundEffect
*/


#ifndef SOUNDEFFECT_HPP_
    #define SOUNDEFFECT_HPP_

    #include <string>
    #include <memory>
    #include <SFML/Audio.hpp>

    #include "Component.hpp"

enum class AudioState {
    STOPPED = 0,
    PLAYING
};

class SoundEffect : public Component {
    public:
        explicit SoundEffect(const std::string& filePath, float volume = 100.0f);
        ~SoundEffect() override = default;

        void play();

        void setVolume(float volume);
        void setPitch(float pitch);
        void setStatus(AudioState state);
        void setGlobal(bool global);
        
        [[nodiscard]] float getVolume() const;
        [[nodiscard]] float getPitch() const;
        [[nodiscard]] bool isGlobal() const;
        [[nodiscard]] AudioState getStatus() const;
        [[nodiscard]] std::shared_ptr<sf::SoundBuffer> getBuffer() const;
        [[nodiscard]] sf::Sound::Status getSfStatus() const;

    private:
        AudioState _state;
        std::shared_ptr<sf::SoundBuffer> _buffer;
        sf::Sound _sound;
        bool _global = false;
    };

#endif