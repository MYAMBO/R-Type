/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** PacketBuilder.cpp
*/

#include "Packet.hpp"
#include "CustomError.hpp"

#include <iomanip>
#include <sstream>
#include <cstring>

/**
 * @brief Constructor for Packet
 */
Packet::Packet() : _dataSize(0), _idSetted(false), _ackSetted(false), _packetNumberSetted(false), _totalPacketNumberSetted(false)
{
}

/**
 * @brief Convert integer to hex string
 */
std::string Packet::toHex(int value, int digits) const
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(digits) << value;
    return oss.str();
}

/**
 * @brief Append hex string to data
 */
void Packet::appendHex(const std::string& hex)
{
    _hexData += hex;
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
    packet.append(_hexData.c_str(), _hexData.size());
    return packet;
}

/**
 * @brief Setter for packet id (unused in hex format)
 */
Packet &Packet::setId(const int id)
{
    (void)id;
    _idSetted = true;
    return *this;
}

/**
 * @brief Setter for packet ack (unused in hex format)
 */
Packet &Packet::setAck(const int ack)
{
    (void)ack;
    _ackSetted = true;
    return *this;
}

/**
 * @brief Setter for Packet packetNbr (unused in hex format)
 */
Packet &Packet::setPacketNbr(const uint8_t packetNbr)
{
    (void)packetNbr;
    _packetNumberSetted = true;
    return *this;
}

/**
 * @brief Setter for Packet totalPacketNbr (unused in hex format)
 */
Packet &Packet::setTotalPacketNbr(const uint8_t totalPacketNbr)
{
    (void)totalPacketNbr;
    _totalPacketNumberSetted = true;
    return *this;
}

/**
 * @brief Write timeSync action in packet
 * @param time The time from serv
 */
void Packet::timeSync(const int time)
{
    appendHex("06");  // opcode
    appendHex(toHex(time, 4));  // 4 hex digits for time
}

/**
 * @brief Write playerPosition action in packet
 * @param id The id of the entity
 * @param x The x coordinate
 * @param y The y coordinate
 */
void Packet::playerPosition(const size_t id, const float x, const float y)
{
    appendHex("07");  // opcode
    appendHex(toHex(static_cast<uint64_t>(id), 16));  // 16 hex digits for id
    appendHex(toHex(0, 2));   // 2 hex digits for type (unused here)
    appendHex(toHex(static_cast<int>(x), 4));   // 4 hex digits for x
    appendHex(toHex(static_cast<int>(y), 4));   // 4 hex digits for y
}

/**
 * @brief Write positionSpawn action in packet
 * @param id The id of the entity
 * @param type The type of entity
 * @param x The x coordinate
 * @param y The y coordinate
 */
void Packet::positionSpawn(const size_t id, const uint16_t type, const float x, const float y)
{
    appendHex("07");  // opcode (same as playerPosition)
    appendHex(toHex(static_cast<uint64_t>(id), 16));    // 16 hex digits for id
    appendHex(toHex(static_cast<int>(type), 2));  // 2 hex digits for type
    appendHex(toHex(static_cast<int>(x), 4));     // 4 hex digits for x
    appendHex(toHex(static_cast<int>(y), 4));     // 4 hex digits for y
}

/**
 * @brief Write hit action in packet
 * @param id The of the entity
 * @param value The value of damage
 */
void Packet::hit(const size_t id, const int value)
{
    appendHex("08");  // opcode
    appendHex(toHex(static_cast<uint64_t>(id), 16));    // 16 hex digits for id
    appendHex(toHex(value, 4));                    // 4 hex digits for damage
}

/**
 * @brief Write dead action in packet
 * @param id The id of the entity
 */
void Packet::dead(const size_t id)
{
    appendHex("09");  // opcode
    appendHex(toHex(static_cast<uint64_t>(id), 16));  // 16 hex digits for id
}

/**
 * @brief Write endGame action in packet
 * @param status Alive or dead (0/1)
 */
void Packet::endGame(const uint8_t status)
{
    appendHex("0A");  // opcode
    appendHex(toHex(static_cast<int>(status), 4));  // 4 hex digits for status
}

/**
 * @brief Write shoot action in packet
 * @param id The id of the shooter
 */
void Packet::shoot(const size_t id) {
    appendHex("0B");  // opcode
    appendHex(toHex(static_cast<uint64_t>(id), 16));  // 16 hex digits for id
}