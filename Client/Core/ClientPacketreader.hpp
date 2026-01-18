/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ClientPacketreader
*/

#ifndef R_TYPE_PACKETREADER_HPP
    #define R_TYPE_PACKETREADER_HPP

#include <SFML/Network.hpp>
#include <memory>
#include "Packet.hpp"
#include "Game.hpp"

/**
 * @brief PacketReader class to read and interpret received data
 */
class ClientPacketreader
{
    public:
        explicit ClientPacketreader(sf::Packet data = sf::Packet(), std::shared_ptr<Game> game = nullptr);
        ~ClientPacketreader() = default;

        void interpretPacket();
        void addPacket(sf::Packet data);
        [[nodiscard]] UDPHeader getHeader() const;
    private:
        sf::Packet _packet;
        UDPHeader _header;
        std::shared_ptr<Game> _game;
};

#endif //R_TYPE_PACKETREADER_HPP