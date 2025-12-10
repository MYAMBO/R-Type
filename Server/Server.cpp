/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Server.cpp
*/

#include "Server.hpp"

Server::Server()
{
    _tcpPort = -1;
    _udpPort = -1;
    _debugMode = false;
}

auto Server::parse(int ac, char **av) -> void
{
    char *endPtr;

    for (int opt = getopt(ac, av, "p:u:hd"); opt != -1; opt = getopt(ac, av, "p:u:hd"))
        switch(opt) {
            case 'p':
                _tcpPort = strtol(optarg, &endPtr, 10);
                if (endPtr == optarg)
                    _tcpPort = -1;
                continue;

            case 'u':
                _udpPort = strtol(optarg, &endPtr, 10);
                if (endPtr == optarg)
                    _udpPort = -1;
                continue;

            case 'd':
                _debugMode = true;
                break;

            case 'h':
                std::cout << "R-TYPE Server - USAGE" << std::endl;
                std::cout << "\t./r-type_server [-d] [-p TcpPort] [-u UdpPort]" << std::endl;
                std::cout << std::endl << "\td : debug mode" << std::endl;
                std::cout <<  "\tp : specify the TCP port (mandatory)" << std::endl;
                std::cout <<  "\tu : specify the UDP port (mandatory)" << std::endl;
                break;

            default :
                std::cerr << "R-TYPE Server - USAGE" << std::endl;
                std::cerr << "\t./r-type_server [-d] [-p TcpPort] [-u UdpPort]" << std::endl;
                std::cerr << std::endl << "\td : debug mode" << std::endl;
                std::cerr <<  "\tp : specify the TCP port (mandatory)" << std::endl;
                std::cerr <<  "\tu : specify the UDP port (mandatory)" << std::endl;
                throw InitServerException("");
        }
    if (_tcpPort == -1)
        throw InitServerException("TCP port must be specified. Check the helper with the -h option.");
    if (_udpPort == -1)
        throw InitServerException("UDP port must be specified. Check the helper with the -h option.");
}


auto Server::initServer() -> void
{
    _tcpListener = sf::TcpListener();
    _udpSocket = sf::UdpSocket();

    if (_tcpListener.listen(_tcpPort) != sf::Socket::Status::Done)
        throw InitServerException();

    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Status::Done)
        throw InitServerException();
}
