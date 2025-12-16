/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ClientPacketreader
*/

#ifndef R_TYPE_PACKETREADER_HPP
    #define R_TYPE_PACKETREADER_HPP

#include <string>

#include "Game.hpp"
#include "MyString.hpp"

/**
 * @brief PacketReader class to read and interpret received data
 */
class ClientPacketreader
{
    public:
        explicit ClientPacketreader(std::string data = "", bool isClient = false, std::shared_ptr<Game> game = nullptr);
        ~ClientPacketreader() = default;

        void interpretPacket();
        void addData(const std::string& data);
        void clear();
    private:
        bool _isClient;
        MyString _data;
        std::shared_ptr<Game> _game;

        void timestamp();
        void updateEntity();
        void hit();
        void dead();
        void endGame();
};


#endif //R_TYPE_PACKETREADER_HPP