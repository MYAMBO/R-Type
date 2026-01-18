/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** PacketBuilder.hpp
*/

#ifndef R_TYPE_PACKET_HPP
    #define R_TYPE_PACKET_HPP
#include <SFML/Network.hpp>
#include <cstdint>

inline int MAX_DATA_SIZE = 116;
inline int HEADER_SIZE = 12;

#pragma pack(push, 1)
struct UDPHeader {
    uint32_t id;
    uint32_t ack;
    uint8_t  packetNbr;
    uint8_t  totalPacketNbr;
    uint16_t dataSize;
};
#pragma pack(pop)

/**
 * @brief Packet class, is a wrapper for sf::packet with useful function
 */
class Packet
{
    public:

        Packet();
        ~Packet() = default;

        Packet& setId(uint32_t id);
        Packet& setAck(uint32_t ack);
        Packet& setPacketNbr(uint8_t packetNbr);
        Packet& setTotalPacketNbr(uint8_t totalPacketNbr);

        void clear();
        void timeSync(uint32_t time);
        void updatePosition(uint32_t id, float x, float y, uint16_t type = 0);
        void Spawn(uint32_t id, uint16_t type, float x, float y);
        void collision(uint32_t entityOneId, uint32_t entityTwoId);
        void dead(uint32_t id);
        void endGame(uint8_t status);
        void action(uint32_t id, uint8_t action, uint32_t data);

        [[nodiscard]] sf::Packet getPacket() const;
    private:
        sf::Packet _payload;
        UDPHeader _header;

        bool _idSetted;
        bool _ackSetted;
        bool _packetNumberSetted;
        bool _totalPacketNumberSetted;
};

#endif //R_TYPE_PACKET_HPP