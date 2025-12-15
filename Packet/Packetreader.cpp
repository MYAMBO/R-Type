/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Packetreader.cpp
*/

#include "Packetreader.hpp"

#include <utility>

/**
 * @brief Construct a packetReader
 * @param data The string to be parsed
 * @param isClient If it's client side or not
 * @param game Pointer to the Server-side game
 */
Packetreader::Packetreader(std::string data, const bool isClient, std::shared_ptr<ServerGame> game) : _isClient(isClient), _data(MyString(std::move(data)))
{
    _game = std::move(game);
}

/**
 * @brief parse the Packet and interpret it
 */
void Packetreader::interpretPacket()
{
    while (_data.size() > 0)
    {
        switch (std::stoi( _data.mySubStr(0, 2) , nullptr, 16)) {
            case 0x06: timestamp(); break;
            case 0x07: updateEntity(); break;
            case 0x08: hit(); break;
            case 0x09: dead(); break;
            case 0x0A: endGame(); break;
            case 0x0B: shoot(); break;
            default:
                break;
        }
    }
}

/**
 * @brief interpret timeStamp action
 */
void Packetreader::timestamp()
{
    int  time = std::stoi( _data.mySubStr(0, 4) , nullptr, 16);

    // call function and give int
}

/**
 * @brief interpret updateEntity action
 */
void Packetreader::updateEntity()
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

/**
 * @brief interpret hit action
 */
void Packetreader::hit()
{
    int id = std::stoi( _data.mySubStr(0, 4), nullptr, 16);
    int damage = std::stoi( _data.mySubStr(0, 4), nullptr, 16);

    // call function and give parameter
}

/**
 * @brief interpret dead action
 */
void Packetreader::dead()
{
    int id = std::stoi( _data.mySubStr(0, 4), nullptr, 16);

    // call function and give parameter
}

/**
 * @brief interpret endGame action
 */
void Packetreader::endGame()
{
    int id = std::stoi(_data.mySubStr(0, 4), nullptr, 16);

    // call function and give parameter
}

/**
 * @brief interpret shoot action
 */
void Packetreader::shoot()
{
    const int id = std::stoi(_data.mySubStr(0, 4), nullptr, 16);

    _serverGame.handleShoot(id);
}
