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
    log("TCP server listening on port " + std::to_string(_tcpPort));
    if (_udpSocket.bind(_udpPort) != sf::Socket::Status::Done)
        throw InitServerException();
    log("UDP server listening on port " + std::to_string(_udpPort));

}

void Server::log(const std::string& message) const
{
    if (_debugMode)
    {
        auto time = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(time);
        std::string time_string = std::ctime(&end_time);
        time_string.erase(time_string.end() - 1, time_string.end());
        std::cout << "[" << time_string << "] " << message << std::endl;

    }
}

void Server::udpThread()
{
    std::array<char, 100> data = {0};
    std::size_t received;

    std::optional<sf::IpAddress> sender;
    unsigned short rport;
    while (true)
    {
        data.fill(0);
        if (_udpSocket.receive(data.data(), data.size(), received, sender, rport) != sf::Socket::Status::Done)
        {
            // error...
        }
        if (received == 0)
            continue;
        data[received - 1] = '\0';
        log("UDP | Received " + std::to_string(received) + " bytes from " + sender.value().toString() + " on port " + std::to_string(rport) + " with value " + data.data());
    }
}

void Server::tcpThread()
{
    while (true)
    {
        _mutex.lock();
        auto tmp_list = _users;
        _mutex.unlock();
        for (const auto& tmp : tmp_list)
        {
            std::array<char, 100> data {};
            std::size_t received;

            data.fill(0);
            if (tmp.getSocket()->receive(data.data(), data.size(), received) != sf::Socket::Status::Done)
                continue;
            data[received - 1] = '\0';
            std::string message;
            log("TCP | Received " + std::to_string(received) + " bytes with value " + data.data() + " from client " + std::to_string(tmp.getId()) + " with port " + std::to_string(tmp.getPort()) + " with ip " + tmp.getIp());
        }
    }
}

}
