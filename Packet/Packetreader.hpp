/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Packetreader.hpp
*/

#ifndef R_TYPE_PACKETREADER_HPP
#define R_TYPE_PACKETREADER_HPP
#include <string>

class Packetreader
{
    public:
        Packetreader(std::string data, bool isClient = false);
        ~Packetreader() = default;

        void interpretPacket();
    private:
        bool _isClient;
        std::string _data;

        void timestamp() const;
        void updateEntity();
        void hit();
        void dead();
        void endGame();
};


#endif //R_TYPE_PACKETREADER_HPP