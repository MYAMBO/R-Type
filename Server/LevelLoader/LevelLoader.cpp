/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** LevelLoader
*/


#include "json.hpp"

#include "LevelLoader.hpp"
#include "GameHelper.hpp"
#include "ServerGame.hpp"

#include <iostream>
#include <fstream>


using json = nlohmann::json;

std::map<int, std::tuple<std::string, std::string>> LevelLoader::_levelsList;

LevelLoader::LevelLoader()
{
    findAllLevel();
}

void LevelLoader::loadFromFile(const int id, ServerGame *server)
{
    try {
        if (_levelsList.find(id) == _levelsList.end()) {
            std::cerr << "ERROR: Level ID " << id << " not found in _levelsList." << std::endl;
            return;
        }
        auto path = std::get<0>(_levelsList[id]);

        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "ERROR: file cannot be open("<< path << ")"  << std::endl;
            return;
        }
        json data;
        file >> data;
        file.close();
        if (data.contains("metadata")) {
            auto &meta = data["metadata"];

            if (meta.contains("name")) {
                std::cout << " Level: " << meta["name"] << std::endl;
            }
        }
        if (!data.contains("entities")) {
            std::cout << "No entities to create\n" << std::endl;
            return;
        }
        std::cout << "Creating enemies:\n" << std::endl;
        for (auto &ent : data["entities"]) {
            float x = ent.value("x", 0.0f);
            float y = ent.value("y", 0.0f);
            std::string type = ent.value("type", "enemy");
            if (server) {
                if (type == "enemy") {
                    server->createEnemy(x, y);
                }
                else if (type == "fast_enemy") {
                    server->createFast(x, y);
                }
                else if (type == "tank_enemy") {
                    server->createTank(x, y);
                }
                else if (type == "sinus_enemy") {
                    server->createSinusEnemy(x, y);
                }
                else if (type == "shooting_enemy") {
                    server->createShootingEnemy(x, y);
                }
                else if (type == "portal_boss") {
                    server->createPortalBoss(x, y);
                }
                else if (type == "heal") {
                    server->createHealPowerUp(x, y);
                }
            }
        }
    } catch (const json::parse_error& e) {
        std::cerr << "\n ERROR JSON: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\n ERROR: " << e.what() << std::endl;
    }
}

void LevelLoader::findAllLevel()
{
    bool findLoop = true;
    std::string path = "../Levels/level";

    for (int i = 1; findLoop; i++) {
        std::string tempPath = path + std::to_string(i) + ".json";
        std::ifstream file(tempPath);

        if (!file.is_open()) {
            findLoop = false;
        } else {
            json data;
            file >> data;
            file.close();

            if (data.contains("metadata")) {
                auto &meta = data["metadata"];

                if (meta.contains("name")) {
                    _levelsList[i] = std::make_tuple(tempPath ,meta["name"].get<std::string>());
                }
            }
        }
    }
}

std::map<int, std::tuple<std::string, std::string>> LevelLoader::getLevelsList()
{
    return _levelsList;
}

int LevelLoader::getLevelsCount()
{
    return static_cast<int>(_levelsList.size());
}
