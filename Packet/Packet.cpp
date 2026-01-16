/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** PacketBuilder.cpp
*/

#include "Packet.hpp"
#include "CustomError.hpp"

#include <cstring>

/**
 * @brief Constructor for Packet
 */
Packet::Packet() : _idSetted(false), _ackSetted(false), _packetNumberSetted(false), _totalPacketNumberSetted(false)
{
    std::memset(&_header, 0, sizeof(UDPHeader));
}

/**
 * @brief Get the packet
 */
sf::Packet Packet::getPacket() const
{
    if (!(_idSetted && _ackSetted && _packetNumberSetted && _totalPacketNumberSetted)) {
        throw MissingPacketParameterError();
    }
    
    sf::Packet packet;
    UDPHeader headerCopy = _header;
    headerCopy.dataSize = static_cast<uint16_t>(_payload.getDataSize());

    packet.append(&headerCopy, sizeof(UDPHeader));
    packet.append(_payload.getData(), _payload.getDataSize());
    return packet;
}

/**
 * @brief Setter for packet id
 * @param id The Id of the Packet
 */
Packet& Packet::setId(const uint32_t id)
{
    _header.id = id;
    _idSetted = true;
    return *this;
}

/**
 * @brief Setter for packet ack
 * @param ack The ack of the Packet
 */
Packet& Packet::setAck(const uint32_t ack)
{
    _header.ack = ack;
    _ackSetted = true;
    return *this;
}

/**
 * @brief Setter for Packet packetNbr
 * @param  packetNbr The number of the Packet
 */
Packet& Packet::setPacketNbr(const uint8_t packetNbr)
{
    _header.packetNbr = packetNbr;
    _packetNumberSetted = true;
    return *this;
}

/**
 * @brief Setter for Packet totalPacketNbr
 * @param totalPacketNbr The total of Packet
 */
Packet& Packet::setTotalPacketNbr(const uint8_t totalPacketNbr)
{
    _header.totalPacketNbr = totalPacketNbr;
    _totalPacketNumberSetted = true;
    return *this;
}

/**
 * @brief Write timeSync action in packet
 * @param time The time from serv
 */
void Packet::timeSync(const uint32_t time)
{
    _payload.clear();
    _payload << static_cast<uint8_t>(0x06); // opcode
    _payload << time;                       // 4 bytes
}

/**
 * @brief Write in packet to update position
 * @param id The id of the entity
 * @param x The x coordinate
 * @param y The y coordinate
 */
void Packet::updatePosition(const uint32_t id, const float x, const float y, uint16_t type)
{
    _payload.clear();
    _payload << static_cast<uint8_t>(0x07); // opcode
    _payload << id;                         // 4 bytes
    _payload << type;                       // 2 bytes
    _payload << x;                          // 4 bytes
    _payload << y;                          // 4 bytes
}

/**
 * @brief Write in packet to spawn entity
 * @param id The id of the entity
 * @param type The type of entity
 * @param x The x coordinate
 * @param y The y coordinate
 */
void Packet::Spawn(const uint32_t id, const uint16_t type, const float x, const float y)
{
    _payload.clear();
    _payload << static_cast<uint8_t>(0x07); // opcode
    _payload << id;                         // 4 bytes
    _payload << type;                       // 2 bytes
    _payload << x;                          // 4 bytes
    _payload << y;                          // 4 bytes
}

/**
 * @brief Write collision in packet
 * @param entityOneId The Id of the first entity
 * @param entityTwoId The Id of the second entity
 */
void Packet::collision(const uint32_t entityOneId, const uint32_t entityTwoId)
{
    _payload.clear();
    _payload << static_cast<uint8_t>(0x08); // opcode
    _payload << entityOneId;                // 4 bytes
    _payload << entityTwoId;                // 4 bytes
}

/**
 * @brief Write dead in packet
 * @param id The id of the entity
 */
void Packet::dead(const uint32_t id)
{
    _payload.clear();
    _payload << static_cast<uint8_t>(0x09); // opcode
    _payload << id;                         // 4 bytes
}

/**
 * @brief Write endGame in packet
 * @param status Alive or dead (0/1)
 */
void Packet::endGame(const uint8_t status)
{
    _payload.clear();
    _payload << static_cast<uint8_t>(0x0A); // opcode
    _payload << status;                     // 1 byte
}

/**
 * @brief Write action in packet
 * @param id The id of the entity doing the action
 * @param action The id of the action who is called 
 */
void Packet::action(const uint32_t id, const uint8_t action, const uint32_t data) {
    _payload.clear();
    _payload << static_cast<uint8_t>(0x0B); // opcode
    _payload << id;                         // 4 bytes
    _payload << action;                     // 1 byte
    _payload << data;                     // 4 byte
}

/**
 * @brief Write in packet to update mana
 * @param playerId The id of the player
 * @param mana The current mana value
 */
void Packet::updateMana(const uint32_t playerId, const int mana)
{
    _payload.clear();
    _payload << static_cast<uint8_t>(0x0C); // opcode
    _payload << playerId;                    // 4 bytes
    _payload << mana;                        // 4 bytes
}