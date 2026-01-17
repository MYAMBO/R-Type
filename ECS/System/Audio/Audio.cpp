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
#include "GameHelper.hpp"
#include "Data.hpp"

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
    auto generalVolume = GameHelper::getEntityByTag(w, "game_volume_settings");
    for (const auto &entity : w.getAllEntitiesWithComponent<SoundEffect>()) {
        auto audioComp = entity->getComponent<SoundEffect>();
        auto sceneComp = entity->getComponent<Scene>();
        if (!sceneComp || !audioComp)
            continue;
        if (sceneComp->getScene() != w.getCurrentScene() && !audioComp->isGlobal())
            continue;
        
        if (audioComp->getStatus() != AudioState::PLAYING)
            continue;
        audioComp->setStatus(AudioState::STOPPED);
        auto buffer = audioComp->getBuffer();
        auto dataComp = generalVolume->getComponent<Data>();
        int masterVolume = std::stoi(dataComp->getData("master_volume")) ;
        int sfxVolume = std::stoi(dataComp->getData("sfx_volume"));
        int finalVolume = (masterVolume * sfxVolume) / 100;
        float volume = static_cast<float>(finalVolume);
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
        auto dataComp = generalVolume->getComponent<Data>();
        int masterVolume = std::stoi(dataComp->getData("master_volume")) ;
        int musicVolume = std::stoi(dataComp->getData("music_volume"));
        int finalVolume = (masterVolume * musicVolume) / 100;
        float volume = static_cast<float>(finalVolume);
        musicComp->setVolume(volume);
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