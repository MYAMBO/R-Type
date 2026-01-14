/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Network
*/

#include <cstring>
#include <iostream>
#include <optional>

#ifdef _WIN32
    #include <io.h>
    #include "getopt.h"
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <netinet/in.h>
    #include <bits/getopt_core.h>
#endif // _WIN32

#include "Game.hpp"
#include "Network.hpp"
#include "MyString.hpp"
#include "ClientPacketreader.hpp"

Network::Network()
    : _ip(sf::IpAddress(0))
{
    _tcpPort = -1;
    _udpPort = -1;
    _debugMode = false;
    _packetReader = ClientPacketreader("", nullptr);
}

void Network::getIpAdress(std::string option)
{
    std::optional<sf::IpAddress> optionalAddress = sf::IpAddress::resolve(option);
    if (!optionalAddress.has_value())
        throw std::runtime_error("Invalid IP address");
    _ip = optionalAddress.value();
}

auto Network::parse(const int ac, char **av) -> void
{
    char *endPtr;

    for (int opt = getopt(ac, av, "p:u:hd"); opt != -1; opt = getopt(ac, av, "p:u:hd"))
        switch(opt) {
            case 'p':
                _tcpPort = strtol(optarg, &endPtr, 10);
                if (endPtr == optarg)
                    _tcpPort = -1;
                break;

            case 'u':
                try
                {
                    getIpAdress(std::string(optarg));
                }
                catch (std::exception e)
                {
                    std::cerr << e.what() << std::endl;
                }
                break;

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

            default:
                std::cerr << "R-TYPE Server - USAGE" << std::endl;
                std::cerr << "\t./r-type_server [-d] [-p TcpPort] [-u UdpPort]" << std::endl;
                std::cerr << std::endl << "\td : debug mode" << std::endl;
                std::cerr <<  "\tp : specify the TCP port (mandatory)" << std::endl;
                std::cerr <<  "\tu : specify the UDP port (mandatory)" << std::endl;
                throw InitClientException("");
        }
    if (_tcpPort == -1)
        throw InitClientException("TCP port must be specified. Check the helper with the -h option.");
}

auto Network::initClient() -> void
{
    if (_tcpClient.connect(_ip, _tcpPort) != sf::Socket::Status::Done)
        throw InitClientException();
    log("TCP server listening on port " + std::to_string(_tcpPort));
    if (_udpSocket.bind(sf::Socket::AnyPort) != sf::Socket::Status::Done)
        throw InitClientException();
    _game = std::make_shared<Game>(*this);
    _packetReader = ClientPacketreader("", _game);
}

void Network::udpThread()
{
    sf::Packet p;

    std::optional<sf::IpAddress> sender;
    unsigned short rport;
    while (true)
    {
        p.clear();
        if (_udpSocket.receive(p, sender, rport) != sf::Socket::Status::Done)
        {

        }
        const void* raw = p.getData();
        const std::size_t size = p.getDataSize();

        const std::string data(static_cast<const char*>(raw), size);
        _packetReader.addData(data);
        try
        {
            _packetReader.interpretPacket();
        }
        catch (std::exception& e)
        {
            _packetReader.clear();
            log("UDP | Failed to interpret packet : " + std::string(e.what()));
        }
        log("UDP | Received " + std::to_string(p.getDataSize()) + " bytes from " + sender.value().toString() + " on port " + std::to_string(rport));
    }
}

void Network::tcpThread()
{
    while (true)
    {
        char data[1024];
        std::size_t received;

        if (_tcpClient.receive(data, sizeof(data), received) != sf::Socket::Status::Done)
            continue;

        if (received < 6)
            continue;

        uint32_t value32;
        std::memcpy(&value32, &data[2], sizeof(value32));
        value32 = ntohl(value32);
        _udpPort = value32;
        _playerId = static_cast<unsigned char>(data[1]);

        _udpSocket.send("", 0, _ip, _udpPort);

        {
            std::lock_guard<std::mutex> lock(_mutex);
            _ready = true;
        }
        _readyCond.notify_all();
    }
}

void Network::log(const std::string& message) const
{
    if (_debugMode)
    {
        const auto time = std::chrono::system_clock::now();
        const std::time_t end_time = std::chrono::system_clock::to_time_t(time);
        std::string time_string = std::ctime(&end_time);
        time_string.erase(time_string.end() - 1, time_string.end());
        std::cout << "[" << time_string << "] " << message << std::endl;
    }
}

void Network::sendPacket(Packet& packet)
{
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _readyCond.wait(lock, [this]{ return _udpPort != -1; });
    }

    const sf::Packet p = packet.getPacket();

    if (_udpSocket.send(p.getData(), p.getDataSize(), _ip, _udpPort) != sf::Socket::Status::Done) {
        log("UDP | Failed to send packet to server");
    }
}

void Network::sendAll(sf::TcpSocket& socket, const void* data, const std::size_t size)
{
    std::size_t sent = 0;

    while (sent < size)
    {
        std::size_t justSent = 0;
        const auto status = socket.send(
            static_cast<const char*>(data) + sent,
            size - sent,
            justSent
        );

        if (status != sf::Socket::Status::Done)
            throw std::runtime_error("TCP send failed");

        sent += justSent;
    }
}

void Network::sendMessage(const std::string &message)
{
    sendAll(_tcpClient, message.data(), message.size());
}

void Network::start()
{
    std::unique_lock<std::mutex> lock(_mutex);
    std::thread tcpThread(&Network::tcpThread, this);
    std::thread udpThread(&Network::udpThread, this);
    _readyCond.wait(lock, [this]{ return _udpPort != -1; });
    lock.unlock();

    _game->loadingRun();
    tcpThread.join();
    udpThread.join();
}
