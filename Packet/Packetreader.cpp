/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Packetreader.cpp
*/

#include "Packetreader.hpp"

#include <utility>

Packetreader::Packetreader(std::string data, const bool isClient) : _isClient(isClient), _data(MyString(std::move(data))){}

void Packetreader::interpretPacket()
{
    switch (int code = std::stoi( _data.mySubStr(0, 2) , nullptr, 16)) {
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

void Packetreader::timestamp()
{
    int  time = std::stoi( _data.mySubStr(0, 4) , nullptr, 16);

    // call function and give int
}

void Packetreader::updateEntity()
{
    int id = std::stoi( _data.mySubStr(0, 4), nullptr, 16);
    int type = std::stoi( _data.mySubStr(0, 2), nullptr, 16);
    int x = std::stoi( _data.mySubStr(0, 4), nullptr, 16);
    int y = std::stoi( _data.mySubStr(0, 4) , nullptr, 16);

    // call function and give parameter
}

void Packetreader::hit()
{
    int id = std::stoi( _data.mySubStr(0, 4), nullptr, 16);
    int damage = std::stoi( _data.mySubStr(0, 4), nullptr, 16);

    // call function and give parameter
}

void Packetreader::dead()
{
    int id = std::stoi( _data.mySubStr(0, 4), nullptr, 16);

    // call function and give parameter
}

void Packetreader::endGame()
{
    int id = std::stoi(_data.mySubStr(0, 4), nullptr, 16);

    // call function and give parameter
}

void Packetreader::shoot()
{
    int id = std::stoi(_data.mySubStr(0, 4), nullptr, 16);

    // call function and give parameter
}
