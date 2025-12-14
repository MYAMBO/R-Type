/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Packetreader.hpp
*/

#ifndef R_TYPE_PACKETREADER_HPP
    #define R_TYPE_PACKETREADER_HPP

#include <string>
#include "MyString.hpp"
#include "ServerGame.hpp"

/**
 * @brief PacketReader class to read and interpret received data
 */
class Packetreader
{
    public:
        explicit Packetreader(std::string data, bool isClient = false);
        ~Packetreader() = default;

        void interpretPacket();
    private:
        bool _isClient;
        MyString _data;
        ServerGame _serverGame;

        void timestamp();
        void updateEntity();
        void hit();
        void dead();
        void endGame();
        void shoot();
};


#endif //R_TYPE_PACKETREADER_HPP