/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** PacketBuilder.hpp
*/

#ifndef R_TYPE_PACKET_HPP
    #define R_TYPE_PACKET_HPP
#include <SFML/Network.hpp>
#include <string>

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

        Packet &setId(int id);
        Packet &setAck(int ack);
        Packet &setPacketNbr(uint8_t packetNbr);
        Packet &setTotalPacketNbr(uint8_t totalPacketNbr);

        void timeSync(int time);
        void playerPosition(size_t id, float x, float y);
        void positionSpawn(size_t id, uint16_t type, float x, float y);
        void hit(size_t id, int value);
        void dead(size_t id);
        void endGame(uint8_t status);
        void shoot(size_t id);

        [[nodiscard]] sf::Packet getPacket() const;
    private:
        std::string _hexData;  // Store data as hex string instead of sf::Packet
        int _dataSize;
        bool _idSetted;
        bool _ackSetted;
        bool _packetNumberSetted;
        bool _totalPacketNumberSetted;

        void appendHex(const std::string& hex);
        std::string toHex(int value, int digits) const;
};

#endif //R_TYPE_PACKET_HPP