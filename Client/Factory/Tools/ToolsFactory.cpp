/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** ToolsFactory
*/

#include "Game.hpp"
#include "Factory.hpp"
#include "ToolsFactory.hpp"

ToolsFactory::ToolsFactory(World& world) : _world(world)
{
}

void ToolsFactory::createGameTools()
{
    auto stats = _world.createEntity();
    stats->addComponent<Tag>("game_stats");
    stats->addComponent<Data>(std::map<std::string, std::string>{
        {"score", "0"},
        {"last_score", "0"},
        {"color_timer", "15"},
        {"high_score", "0"}
    });
    auto volume = _world.createEntity();
    volume->addComponent<Scene>(static_cast<int>(SceneType::LOADING));
    volume->addComponent<Data>(std::map<std::string, std::string>{
        {"music_volume", "100"},
        {"sfx_volume", "100"},
        {"master_volume", "100"}
    });
    volume->addComponent<Tag>("game_volume_settings");
    volume->addComponent<Script>(volumeSettingsScript);

    auto difficulty = _world.createEntity();
    difficulty->addComponent<Scene>(static_cast<int>(SceneType::LOADING));
    difficulty->addComponent<Data>(std::map<std::string, std::string>{
        {"is_easy_mode", "false"},
        {"is_hard_mode", "false"},
        {"is_god_mode", "false"},
    });
    difficulty->addComponent<Tag>("game_difficulty_settings");
    
    auto availability = _world.createEntity();
    availability->addComponent<Scene>(static_cast<int>(SceneType::LOADING));
    availability->addComponent<Data>(std::map<std::string, std::string>{
        {"is_color_blind", "normal"},
        {"disclexia_mode", "false"},
        {"lastfont_used", "regular"},
        {"language", "en"}
    });
    availability->addComponent<Tag>("game_availability_settings");
    availability->addComponent<Script>(availabilitySettingsScript);

    auto controls = _world.createEntity();
    controls->addComponent<Scene>(0);
    controls->addComponent<Tag>("game_controls_settings");
    controls->addComponent<Data>(std::map<std::string, std::string>{
        {"UP", "Z"},
        {"DOWN", "S"},
        {"LEFT", "Q"},
        {"RIGHT", "D"},
        {"SHOOT", "Space"}
    });
}