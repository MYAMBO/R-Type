/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** PacketBuilder.cpp
*/

#include "Packet.hpp"
#include "CustomError.hpp"

#include <cstring>

Packet::Packet() : _dataSize(0), _idSetted(false), _ackSetted(false), _packetNumberSetted(false), _totalPacketNumberSetted(false)
{
    constexpr char zeros[12] = {};
    _packet.append(zeros, 12);
}

sf::Packet Packet::getPacket() const
{
    if (_idSetted && _ackSetted && _packetNumberSetted && _totalPacketNumberSetted) {
        setDataSize(_dataSize);
        return _packet;
    }
    throw MissingPacketParameterError();
}


void Packet::setId(const int id)
{
    std::memcpy(static_cast<char*>(const_cast<void*>(_packet.getData())), &id, sizeof(int));
    _idSetted = true;
}

void Packet::setAck(const int ack)
{
    constexpr int offset = 4;
    std::memcpy(static_cast<char*>(const_cast<void*>(_packet.getData())) + offset, &ack, sizeof(int));
    _ackSetted = true;
}

void Packet::setPacketNbr(const uint8_t packetNbr)
{
    constexpr int offset = 8;
    std::memcpy(static_cast<char*>(const_cast<void*>(_packet.getData())) + offset, &packetNbr, sizeof(uint8_t));
    _packetNumberSetted = true;
}

void Packet::setTotalPacketNbr(const uint8_t totalPacketNbr)
{
    constexpr int offset = 9;
    std::memcpy(static_cast<char*>(const_cast<void*>(_packet.getData())) + offset, &totalPacketNbr, sizeof(uint8_t));
    _totalPacketNumberSetted = true;
}

void Packet::setDataSize(const uint16_t dataSize) const
{
    constexpr int offset = 10;
    std::memcpy(static_cast<char*>(const_cast<void*>(_packet.getData())) + offset, &dataSize, sizeof(uint16_t));
}


void Packet::timeSync(const int time)
{
    constexpr int size = sizeof(uint8_t) + sizeof(int);

    if (_dataSize + size > MAX_DATA_SIZE)
        throw PacketFullError();

    _packet << uint8_t{0x06} << time;
    _dataSize += size;
}

void Packet::playerPosition(const int id, const float x, const float y)
{
    constexpr int size = sizeof(uint8_t) + sizeof(int) + (sizeof(float) * 2);

    if (_dataSize + size > MAX_DATA_SIZE)
        throw PacketFullError();

    _packet << uint8_t{0x07} << id << x << y;
    _dataSize += size;
}

void Packet::positionSpawn(const int id, const uint16_t type, const float x, const float y)
{
    constexpr int size = sizeof(uint8_t) + sizeof(int) + sizeof(uint16_t) + (sizeof(float) * 2);

    if (_dataSize + size > MAX_DATA_SIZE)
        throw PacketFullError();

    _packet << uint8_t{0x07} << id << type << x << y;
    _dataSize += size;
}

void Packet::hit(const int id, const int value)
{
    constexpr int size = sizeof(uint8_t) + (sizeof(int) * 2);

    if (_dataSize + size > MAX_DATA_SIZE)
        throw PacketFullError();

    _packet << uint8_t{0x08} << id << value;
    _dataSize += size;
}

void Packet::dead(const int id)
{
    constexpr int size = sizeof(uint8_t) + sizeof(int);

    if (_dataSize + size > MAX_DATA_SIZE)
        throw PacketFullError();

    _packet << uint8_t{0x09} << id;
    _dataSize += size;
}

void Packet::endGame(const uint8_t status)
{
    constexpr int size = (sizeof(uint8_t) * 2);

    if (_dataSize + size > MAX_DATA_SIZE)
        throw PacketFullError();

    _packet << uint8_t{0x0A} << status;
    _dataSize += size;
}
