/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Server.hpp
*/

#ifndef SERVER
#define SERVER

#include <thread>
#include <utility>
#include <iostream>
#include <mutex>
#include <cstring>
#include <unistd.h>

#include "IGameNetwork.hpp"
#include "Packet.hpp"
#include "Packetreader.hpp"
#include "ServerGame.hpp"
#include "User.hpp"
#include "SFML/Network.hpp"

class Server : public IGameNetwork
{
    public:
        Server();
        ~Server() = default;
        void initServer();
        void start();
        void parse(int ac, char** av);
        void log(const std::string& message) const;
        void udpThread();
        void tcpThread();
        void accepterThread();
        void sendPacket(const Packet& packet) override;
        void sendMessage(std::string message, sf::IpAddress ip, unsigned short port);
        void sendMessage(std::string message, unsigned int playerId);
        static void sendAll(sf::TcpSocket& socket, const void* data, std::size_t size);

        class InitServerException : public std::exception
        {
            public:
                explicit InitServerException(std::string message = "")
                {
                    _message = std::move(message);
                };

                [[nodiscard]] const char* what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;
        };

    private:
        sf::UdpSocket _udpSocket;
        sf::TcpListener _tcpListener;
        sf::TcpSocket _tcpClient;
        std::thread _udpThread;
        long _tcpPort;
        long _udpPort;
        bool _debugMode;
        std::vector<User> _users;
        std::mutex _mutex;
        std::shared_ptr<ServerGame> _game;
        Packetreader _packetReader;
};
#endif // SERVER
