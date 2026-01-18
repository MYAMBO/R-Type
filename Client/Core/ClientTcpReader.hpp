/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ClientTcpReader.hpp
*/

#ifndef R_TYPE_CLIENTTCPREADER_HPP
    #define R_TYPE_CLIENTTCPREADER_HPP

#include <memory>
#include <string>
#include <vector>

#include "Game.hpp"


class Game;

class ClientTcpReader
{
    public:
        ClientTcpReader(std::shared_ptr<Game> game);
        ~ClientTcpReader() = default;

        std::string InterpretData(const std::string& data);

    private:

        std::shared_ptr<Game> _game;
};


#endif //R_TYPE_CLIENTTCPREADER_HPP