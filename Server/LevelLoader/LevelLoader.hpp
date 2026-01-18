/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** LevelLoader
*/

#ifndef R_TYPE_LEVELLOADER_HPP
    #define R_TYPE_LEVELLOADER_HPP

#include <string>
#include <map>
#include <tuple>

class ServerGame;

class LevelLoader
{
    public:
        LevelLoader();
        ~LevelLoader() = default;

        static void loadFromFile(int id, ServerGame *server);

    private:
        // A map with ID -> tuple (map path, map name)
        static std::map<int,  std::tuple<std::string, std::string>> _levelsList;

        static void findAllLevel();
};


#endif //R_TYPE_LEVELLOADER_HPP