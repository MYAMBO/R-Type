/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ClientPacketreader
*/


#include "ClientPacketreader.hpp"

#include <iostream>
#include <utility>
#include <cstring>

/**
 * @brief Construct a packetReader
 * @param data The string to be parsed
 * @param isClient If it's client side or not
 * @param game Pointer to the Server-side game
 */
ClientPacketreader::ClientPacketreader(std::string data, std::shared_ptr<Game> game) : _data(MyString(std::move(data)))
{
    _game = std::move(game);
}

/**
 * @brief parse the Packet and interpret it
 */
void ClientPacketreader::interpretPacket()
{
    while (_data.size() > 0)
    {
        auto truc = std::stoi( _data.mySubStr(0, 2) , nullptr, 16);
        switch (truc) {
            case 0x06: timestamp(); break;
            case 0x07: updateEntity(); break;
            case 0x08: hit(); break;
            case 0x09: dead(); break;
            case 0x0A: endGame(); break;
            default:
                break;
        }
    }
}

/**
 * @brief interpret timeStamp action
 */
void ClientPacketreader::timestamp()
{
    int  time = std::stoi( _data.mySubStr(0, 4) , nullptr, 16);

    // call function and give int
}

/**
 * @brief interpret updateEntity action
 */
void ClientPacketreader::updateEntity()
{
    unsigned int id = std::stoul( _data.mySubStr(0, 16), nullptr, 16);
    int type = std::stoi( _data.mySubStr(0, 2), nullptr, 16);
    float x = static_cast<float>(std::stoi(_data.mySubStr(0, 4), nullptr, 16));
    float y = static_cast<float>(std::stoi(_data.mySubStr(0, 4), nullptr, 16));

    _game->handleSpawn(id, type, x, y);
}

void ClientPacketreader::clear()
{
    _data.clear();
}

/**
 * @brief interpret hit action
 */
void ClientPacketreader::hit()
{
    int id = std::stoi( _data.mySubStr(0, 16), nullptr, 16);
    int damage = std::stoi( _data.mySubStr(0, 4), nullptr, 16);

    // call function and give parameter
}

/**
 * @brief interpret dead action
 */
void ClientPacketreader::dead()
{
    int id = std::stoi( _data.mySubStr(0, 16), nullptr, 16);

    _game->killEntity(id);
}

/**
 * @brief interpret endGame action
 */
void ClientPacketreader::endGame()
{
    unsigned int id = std::stoi(_data.mySubStr(0, 16), nullptr, 16);

    // call function and give parameter
}

/**
 * @brief interpret shoot action
 */
void ClientPacketreader::addData(const std::string& data)
{
    _data.append(data.data(), data.size());
}
