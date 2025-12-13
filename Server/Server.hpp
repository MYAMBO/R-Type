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
#include <unistd.h>

#include "User.hpp"
#include "SFML/Network.hpp"

class Server
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
};
#endif // SERVER
