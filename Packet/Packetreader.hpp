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
        explicit Packetreader(std::string data = "", bool isClient = false, std::shared_ptr<ServerGame> game = nullptr);
        ~Packetreader() = default;

        void interpretPacket();
        void addData(const std::string& data);
    private:
        bool _isClient;
        MyString _data;
        std::shared_ptr<ServerGame> _game;

        void timestamp();
        void updateEntity();
        void hit();
        void dead();
        void endGame();
        void shoot();
};


#endif //R_TYPE_PACKETREADER_HPP