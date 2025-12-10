/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** PacketBuilder.hpp
*/

#ifndef R_TYPE_PACKET_HPP
    #define R_TYPE_PACKET_HPP
#include <SFML/Network.hpp>

inline int MAX_DATA_SIZE = 116;
inline int HEADER_SIZE = 12;

/**
 * @brief Packet class, is a wrapper for sf::packet with useful function
 */
class Packet
{
    public:

        Packet();
        ~Packet() = default;

        void setId(int id);
        void setAck(int ack);
        void setPacketNbr(uint8_t packetNbr);
        void setTotalPacketNbr(uint8_t totalPacketNbr);

        void timeSync(int time);
        void playerPosition(int id, float x, float y);
        void positionSpawn(int id, uint16_t type, float x, float y);
        void hit(int id, int value);
        void dead(int id);
        void endGame(uint8_t status);
        void shoot(int id);

        sf::Packet getPacket() const;
    private:
        sf::Packet _packet;
        int _dataSize;
        bool _idSetted;
        bool _ackSetted;
        bool _packetNumberSetted;
        bool _totalPacketNumberSetted;

        void setDataSize(uint16_t dataSize) const;
};

#endif //R_TYPE_PACKET_HPP