/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ClientPacketreader
*/


#include "ClientPacketreader.hpp"

#include <utility>

/**
 * @brief Construct a packetReader
 * @param data The string to be parsed
 * @param isClient If it's client side or not
 * @param game Pointer to the Server-side game
 */
ClientPacketreader::ClientPacketreader(std::string data, const bool isClient, std::shared_ptr<Game> game) : _isClient(isClient), _data(MyString(std::move(data)))
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
        switch (std::stoi( _data.mySubStr(0, 2) , nullptr, 16)) {
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
    if (_isClient)
    {
        int id = std::stoi( _data.mySubStr(0, 4), nullptr, 16);
        int type = std::stoi( _data.mySubStr(0, 2), nullptr, 16);
        int x = std::stoi( _data.mySubStr(0, 4), nullptr, 16);
        int y = std::stoi( _data.mySubStr(0, 4) , nullptr, 16);

        // call function and give parameter
    } else {
        int id = std::stoi( _data.mySubStr(0, 4), nullptr, 16);
        int x = std::stoi( _data.mySubStr(0, 4), nullptr, 16);
        int y = std::stoi( _data.mySubStr(0, 4) , nullptr, 16);
    }
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
    int id = std::stoi( _data.mySubStr(0, 4), nullptr, 16);
    int damage = std::stoi( _data.mySubStr(0, 4), nullptr, 16);

    // call function and give parameter
}

/**
 * @brief interpret dead action
 */
void ClientPacketreader::dead()
{
    int id = std::stoi( _data.mySubStr(0, 4), nullptr, 16);

    // call function and give parameter
}

/**
 * @brief interpret endGame action
 */
void ClientPacketreader::endGame()
{
    int id = std::stoi(_data.mySubStr(0, 4), nullptr, 16);

    // call function and give parameter
}

/**
 * @brief interpret shoot action
 */
void ClientPacketreader::addData(const std::string& data)
{
    _data.append(data.c_str());
}
