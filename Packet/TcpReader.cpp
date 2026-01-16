/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TcpReader.cpp
*/

#include "TcpReader.hpp"
#include <cstdint>
#include <array>

TcpReader::TcpReader()
{

}

std::string TcpReader::loginRequest(const std::string& data)
{
    (void)data;
    std::array<std::uint8_t, 1> buffer{};
    buffer[0] = 0x02;
    std::string message(
        reinterpret_cast<const char*>(buffer.data()),
        buffer.size()
    );
    return message;
}


std::string TcpReader::InterpretData(const std::string& data)
{
    if (data.empty())
        return {};
    switch (data.at(0))
    {
    case 2:
        return loginRequest(data);
    default:
        return {"undefined"};
    }
}
