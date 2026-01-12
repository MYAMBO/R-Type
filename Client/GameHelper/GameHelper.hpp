/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GameHelper
*/

#ifndef GAMEHELPER_HPP_
    #define GAMEHELPER_HPP_

    #include <memory>
    #include "World.hpp"
    #include "Camera.hpp"

/**
 * @brief GameHelper class providing utility functions for game entities.
*/
class GameHelper {
    public:
        GameHelper() = delete; 
        ~GameHelper() = delete;

        static sf::Color hueToRGB(float hue);
        static std::shared_ptr<Camera> getMainCamera(World &world);
        static std::shared_ptr<Entity> getEntityById(World &world, uint64_t id);
        static std::shared_ptr<Entity> getEntityByTag(World &world, const std::string &tag);
        static std::vector<std::shared_ptr<Entity>> getEntitiesByGroup(World &world, size_t groupId);
        static void createSparks(World &world, float x, float y, int amount);

        static void createBasicEnemy(World &world, float x, float y, int entityId);
        static void createSinusEnemy(World &world, float x, float y, int entityId);
};

#endif /* !GAMEHELPER_HPP_ */