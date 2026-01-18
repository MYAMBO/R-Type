/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** User.hpp
*/

#ifndef USER
#define USER

#include <memory>
#include "SFML/Network.hpp"

class User
{
    public:
        User(unsigned short port, std::string ip,
             std::shared_ptr<sf::TcpSocket> socket);
        ~User() = default;
        [[nodiscard]] std::shared_ptr<sf::TcpSocket> getSocket() const;
        [[nodiscard]] unsigned int getId() const;
        [[nodiscard]] unsigned short getPort() const;
        [[nodiscard]] std::string getName() const;
        [[nodiscard]] std::string getIp() const;
        std::vector<u_int32_t> _ackList;

    private:
        std::shared_ptr<sf::TcpSocket> _socket;
        unsigned int _id;
        unsigned short _port;
        unsigned int _udpPort;
        std::string _name;
        std::string _ip;
};
#endif // USER
