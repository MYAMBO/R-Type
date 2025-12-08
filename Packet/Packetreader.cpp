/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Packetreader.cpp
*/

#include "Packetreader.hpp"

#include <functional>
#include <unordered_map>
#include <utility>

Packetreader::Packetreader(std::string data, const bool isClient) : _isClient(isClient), _data(std::move(data)){}

void Packetreader::interpretPacket()
{
    int code = std::stoi( _data.substr(0, 2), nullptr, 16);

    switch (code) {
        case 0x06: timestamp(); break;
        case 0x07: updateEntity(); break;
        case 0x08: hit(); break;
        case 0x09: dead(); break;
        case 0x0A: endGame(); break;
        default:
            break;
    }
}

void Packetreader::timestamp() const
{
    int  time = std::stoi(_data.substr(0, 4), nullptr, 16);

    //call function and give int
}
