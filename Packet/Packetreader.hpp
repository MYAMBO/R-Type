/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Packetreader.hpp
*/

#ifndef R_TYPE_PACKETREADER_HPP
    #define R_TYPE_PACKETREADER_HPP

#include <SFML/Network.hpp>
#include <memory>
#include "Packet.hpp"
#include "ServerGame.hpp"

/**
 * @brief PacketReader class to read and interpret received data
 */
class Packetreader
{
    public:
        explicit Packetreader(sf::Packet data = sf::Packet(), std::shared_ptr<ServerGame> game = nullptr);
        ~Packetreader() = default;

        void interpretPacket();
        void addPacket(sf::Packet data);
        void clear();
        [[nodiscard]] UDPHeader getHeader() const;

    private:
        sf::Packet _packet;
        UDPHeader _header;
        std::shared_ptr<ServerGame> _game;
};


#endif //R_TYPE_PACKETREADER_HPP