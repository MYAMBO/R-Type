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

        static std::shared_ptr<Camera> getMainCamera(World &world);
        static std::shared_ptr<Entity> getEntityById(World &world, uint64_t id);
        static std::shared_ptr<Entity> getEntityByTag(World &world, const std::string &tag);

        static void createBasicEnemy(World &world, float x, float y);
};

#endif /* !GAMEHELPER_HPP_ */