/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Server.hpp
*/

#ifndef SERVER
#define SERVER
#include "TcpReader.hpp"

#ifdef _WIN32
    #include <io.h>
    #include "getopt.h"
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <netinet/in.h>
    #include <unistd.h>
#endif // _WIN32

#include <thread>
#include <utility>
#include <mutex>

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
        void sendPacket(Packet& packet) override;
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
        TcpReader _tcpReader;
        std::vector<std::pair<std::string, unsigned short>> _udpUsers;
        std::vector<std::pair<Packet, u_int32_t>> _ackPackets;
        u_int32_t _tick;
};
#endif // SERVER
