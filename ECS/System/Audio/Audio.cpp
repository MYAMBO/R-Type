/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Audio System
*/

#include <thread>
#include <chrono>

#include "Tag.hpp"
#include "Scene.hpp"
#include "Music.hpp"
#include "SoundEffect.hpp"

#include "Audio.hpp"

/**
 * @brief Update the audio system.
 * It checks all entities with SoundEffect components and plays sounds in a detached thread if their state is PLAYING.
 * @param dt Delta time (not used)
 * @param w Reference to the world containing entities and components
*/
void Audio::update(const float &dt, World &w)
{
    (void)dt;
    for (const auto &entity : w.getAllEntitiesWithComponent<SoundEffect>()) {
        auto audioComp = entity->getComponent<SoundEffect>();
        auto sceneComp = entity->getComponent<Scene>();
        if (!sceneComp || !audioComp)
            continue;
        if (sceneComp->getScene() != w.getCurrentScene())
            continue;

        if (audioComp->getStatus() != AudioState::PLAYING)
            continue;
        audioComp->setStatus(AudioState::STOPPED);
        auto buffer = audioComp->getBuffer();
        float volume = audioComp->getVolume();
        std::thread([buffer, volume]() {
            sf::Sound sound(*buffer);
            sound.setVolume(volume);
            sound.play();
            while (sound.getStatus() == sf::Sound::Status::Playing) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }).detach();
    }
    for (const auto &entity : w.getAllEntitiesWithComponent<Music>()) {
        auto musicComp = entity->getComponent<Music>();
        if (!musicComp)
            continue;

        auto& sfMusic = musicComp->getInternalMusic();

        switch (musicComp->getState()) {
            case MusicState::PLAYING:
                if (sfMusic.getStatus() != sf::Music::Status::Playing)
                    sfMusic.play();
                break;
            case MusicState::PAUSED:
                if (sfMusic.getStatus() == sf::Music::Status::Playing)
                    sfMusic.pause();
                break;
            case MusicState::STOPPED:
                if (sfMusic.getStatus() != sf::Music::Status::Stopped)
                    sfMusic.stop();
                break;
        }
    }
}