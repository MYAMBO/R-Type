/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** Music Component
*/

#ifndef MUSIC_HPP_
    #define MUSIC_HPP_

    #include <string>
    #include <SFML/Audio.hpp>

    #include "Component.hpp"

enum class MusicState {
    PLAYING,
    PAUSED,
    STOPPED
};

class Music : public Component {
    public:
        explicit Music(const std::string& filePath, float volume = 50.0f, bool loop = true);
        ~Music() override = default;

        void play();
        void pause();
        void stop();

        void setVolume(float volume);
        void setLoop(bool loop);
        void setPitch(float pitch);

        [[nodiscard]] float getVolume() const;
        [[nodiscard]] bool isLooping() const;
        [[nodiscard]] MusicState getState() const;

        sf::Music& getInternalMusic() { return _music; }

    private:
        sf::Music _music;
        MusicState _targetState;
};

#endif /* !MUSIC_HPP_ */