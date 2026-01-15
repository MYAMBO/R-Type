/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ClientPacketreader
*/


#include "ClientPacketreader.hpp"

#include <utility>
#include <cstring>

/**
 * @brief Construct a packetReader
 * @param data The packet to be parsed
 * @param game Pointer to the Game
 */
ClientPacketreader::ClientPacketreader(sf::Packet data, std::shared_ptr<Game> game) : _packet(std::move(data))
{
    _game = std::move(game);
}

/**
 * @brief parse the Packet and interpret it
 */
void ClientPacketreader::interpretPacket()
{
    if (_packet.getDataSize() < sizeof(UDPHeader)) {
        return;
    }

    // Extraire le header
    std::memcpy(&_header, _packet.getData(), sizeof(UDPHeader));

    sf::Packet payload;
    const char* dataPtr = static_cast<const char*>(_packet.getData());
    payload.append(dataPtr + sizeof(UDPHeader), _packet.getDataSize() - sizeof(UDPHeader));

    while (!payload.endOfPacket())
    {
        uint8_t opcode;
        if (!(payload >> opcode)) break;

        switch (opcode) {
            case 0x06: {
                uint32_t time;
                if (payload >> time) {
                    std::cout << "TimeSync received: " << time << std::endl;
                }
                break;
            }
            case 0x07: {
                uint32_t id;
                uint16_t type;
                float x, y;
                if (payload >> id >> type >> x >> y) {
                    printf("Update entity received: id=%u, type=%d, x=%f, y=%f\n", id, type, x, y);
                    if (_game) _game->updateEntity(id, type, x, y);
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
                    std::cout << "Entity " << id << " dead" << std::endl;
                    if (_game)
                        _game->killEntity(id);
                }
                break;
            }
            case 0x0A: {
                uint8_t status;
                if (payload >> status) {
                    std::cout << "EndGame: " << static_cast<int>(status) << std::endl;
                }
                break;
            }
            case 0x0B: {
                uint32_t id;
                uint8_t actionId;
                uint32_t data;
                if (payload >> id >> actionId >> data) {
                    _game->handleAction(id, actionId, data);
                }
                break;
            }
            case 0x0C: {
                uint32_t playerId;
                int mana;
                if (payload >> playerId >> mana) {
                    if (_game)
                        _game->updatePlayerMana(playerId, mana);
                }
                break;
            }
            default:
                return;
        }
    }
}

/**
 * @brief add packet data
 */
void ClientPacketreader::addPacket(sf::Packet data)
{
    _packet = std::move(data);
}
