/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** LevelLoader
*/

#ifndef R_TYPE_LEVELLOADER_HPP
    #define R_TYPE_LEVELLOADER_HPP

#include <iostream>
#include <string>

#include "World.hpp"
#include "ServerGame.hpp"



class LevelLoader
{
    public:
        LevelLoader() = default;
        ~LevelLoader() = default;

        static void loadFromFile(const std::string &path, ServerGame *server);

};


#endif //R_TYPE_LEVELLOADER_HPP