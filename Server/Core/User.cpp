/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** User.cpp
*/

#include "User.hpp"

static auto getUserId() -> unsigned int
{
    static unsigned int id = 0;
    return id++;
}

User::User(const unsigned short port, std::string ip, std::shared_ptr<sf::TcpSocket> socket)
{
    _id = getUserId();
    _port = port;
    _udpPort = 0;
    _ip = std::move(ip);
    _socket = std::move(socket);
}

unsigned int User::getId() const
{
    return _id;
}

std::string User::getIp() const
{
    return _ip;
}

std::string User::getName() const
{
    return _name;
}

unsigned short User::getPort() const
{
    return _port;
}

std::shared_ptr<sf::TcpSocket> User::getSocket() const
{
    return _socket;
}
