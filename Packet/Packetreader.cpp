/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Packetreader.cpp
*/

#include "Packetreader.hpp"

#include <iostream>
#include <utility>
#include <cstring>

/**
 * @brief Construct a packetReader
 * @param data The packet to be parsed
 * @param game Pointer to the Server-side game
 */
Packetreader::Packetreader(sf::Packet data, std::shared_ptr<ServerGame> game) : _packet(std::move(data))
{
    _header.id = 0;
    _header.packetNbr = 0;
    _game = std::move(game);
}

/**
 * @brief parse the Packet and interpret it
 */
void Packetreader::interpretPacket()
{
    if (_packet.getDataSize() < sizeof(UDPHeader)) {
        std::cerr << "Packet too small to contain header" << std::endl;
        return;
    }

    std::memcpy(&_header, _packet.getData(), sizeof(UDPHeader));

    sf::Packet payload;
    const char* dataPtr = static_cast<const char*>(_packet.getData());
    payload.append(dataPtr + sizeof(UDPHeader), _packet.getDataSize() - sizeof(UDPHeader));

    std::cout << "server received packet from ID: " << _header.id << std::endl;

    while (!payload.endOfPacket())
    {
        uint8_t opcode;
        if (!(payload >> opcode)) break;

        switch (opcode) {
            case 0x06: {
                uint32_t time;
                if (payload >> time) {
                    std::cout << "TimeSync: " << time << std::endl;
                    // _game->handleTimeSync(time);
                }
                break;
            }
            case 0x07: {
                uint32_t id;
                uint16_t type;
                float x, y;
                if (payload >> id >> type >> x >> y) {
                    if (type == 0) {
                        std::cout << "Player " << id << " moved to (" << x << ", " << y << ")" << std::endl;
                        if (_game) _game->serverUpdatePosition(id, x, y);
                    } else {
                        std::cout << "New player " << id << " spawning at (" << x << ", " << y << ")" << std::endl;
                        if (_game) _game->handleNewPlayer();
                    }
                }
                break;
            }
            case 0x08: {
                uint32_t id1, id2;
                if (payload >> id1 >> id2) {
                    std::cout << "Collision between " << id1 << " and " << id2 << std::endl;
                }
                break;
            }
            case 0x09: {
                uint32_t id;
                if (payload >> id) {
                    std::cout << "Entity " << id << " is dead" << std::endl;
                }
                break;
            }
            case 0x0A: {
                uint8_t status;
                if (payload >> status) {
                    std::cout << "EndGame status: " << static_cast<int>(status) << std::endl;
                }
                break;
            }
            case 0x0B: {
                uint32_t id;
                uint8_t actionId;
                uint32_t data;
                if (payload >> id >> actionId >> data) {
                    std::cout << "Action " << static_cast<int>(actionId) << " from " << id << std::endl;
                    if (_game) _game->handleAction(id, actionId, data);
                }
                break;
            }
            default:
                std::cerr << "Unknown opcode: " << static_cast<int>(opcode) << std::endl;
                return;
        }
    }
}

void Packetreader::clear()
{
    _packet.clear();
}

/**
 * @brief add packet data
 */
void Packetreader::addPacket(sf::Packet data)
{
    _packet = std::move(data);
}
