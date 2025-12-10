/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** User.hpp
*/

#pragma once
#include <memory>
#include "SFML/Network.hpp"

class User
{
public:
    User(unsigned int port, std::string ip, std::shared_ptr<sf::TcpSocket> socket);
    ~User() = default;
    std::shared_ptr<sf::TcpSocket> getSocket() const;
    unsigned int getId() const;
    unsigned int getPort() const;
    std::string getName() const;
    std::string getIp() const;

private:
    std::shared_ptr<sf::TcpSocket> _socket;
    unsigned int _id;
    unsigned int _port;
    std::string _name;
    std::string _ip;
};
