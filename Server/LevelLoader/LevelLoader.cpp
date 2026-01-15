/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** LevelLoader
*/


#include "json.hpp"

#include "LevelLoader.hpp"
#include "World.hpp"
#include "GameHelper.hpp"

#include <iostream>
#include <fstream>


using json = nlohmann::json;

void LevelLoader::loadFromFile(const std::string &path, ServerGame *server)
{
    try {
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
            }
        }
    } catch (const json::parse_error& e) {
        std::cerr << "\n ERROR JSON: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\n ERROR: " << e.what() << std::endl;
    }
}

