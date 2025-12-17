/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Server.cpp
*/

#include "Server.hpp"

#include <netinet/in.h>

Server::Server()
{
    _tcpPort = -1;
    _udpPort = -1;
    _debugMode = false;
    _game = std::make_shared<ServerGame>(*this);
    _packetReader = Packetreader("", _game);
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
    sf::Packet p;

    std::optional<sf::IpAddress> sender;
    unsigned short rport;
    while (true)
    {
        p.clear();
        if (_udpSocket.receive(p, sender, rport) != sf::Socket::Status::Done)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
        if (!sender.has_value())
            continue;

        const void* raw = p.getData();
        const std::size_t size = p.getDataSize();

        std::string data(static_cast<const char*>(raw), size);
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
        bool found = false;

        for (const auto& [fst, snd] : _udpUsers)
            if (fst == sender.value().toString() && snd == rport)
                found = true;
        if (found == false)
            _udpUsers.push_back(std::make_pair<>(sender.value().toString(), rport));
        log("UDP | Received " + std::to_string(p.getDataSize()) + " bytes from " + sender.value().toString() + " on port " + std::to_string(rport));
    }
}

void Server::tcpThread()
{
    while (true)
    {
        _mutex.lock();
        auto tmp_list = _users;
        _mutex.unlock();

        bool dataReceived = false;
        for (const auto& tmp : tmp_list)
        {
            std::array<char, 1024> data {};
            std::size_t received;

            data.fill(0);
            if (tmp.getSocket()->receive(data.data(), data.size(), received) != sf::Socket::Status::Done)
                continue;

            dataReceived = true;
            data[received - 1] = '\0';
            std::string message;
            log("TCP | Received " + std::to_string(received) + " bytes with value " + data.data() + " from client " + std::to_string(tmp.getId()) + " with port " + std::to_string(tmp.getPort()) + " with ip " + tmp.getIp());
        }

        if (!dataReceived)
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Server::accepterThread()
{
    while (true)
    {
        if (_tcpListener.accept(_tcpClient) != sf::Socket::Status::Done)
            continue;
        unsigned short port = _tcpClient.getRemotePort();
        std::string ip = _tcpClient.getRemoteAddress().value().toString();
        log("Connected with port " + std::to_string(port) +
            " at address " +
            (_tcpClient.getRemoteAddress().has_value() ?
                ip : ""));
        _tcpClient.setBlocking(false);

        std::array<std::uint8_t, 6> buffer{};
        buffer[0] = 0x01;
        unsigned int playerId;

        {
            std::lock_guard<std::mutex> lock(_mutex);
            _users.emplace_back(port, ip, std::make_shared<sf::TcpSocket>(std::move(_tcpClient)));
            playerId = _users.back().getId();
            buffer[1] = static_cast<std::uint8_t>(playerId);
        }

        std::uint32_t udpPort = htonl(_udpPort);
        std::memcpy(&buffer[2], &udpPort, sizeof(udpPort));

        std::string message(
            reinterpret_cast<const char*>(buffer.data()),
            buffer.size()
        );

        sendMessage(message, playerId);
    }
}

void Server::sendPacket(Packet& packet)
{
    packet.setId(0);
    packet.setAck(0);
    packet.setPacketNbr(1);
    packet.setTotalPacketNbr(1);
    const sf::Packet p = packet.getPacket();

    for (auto &[fst, snd] : _udpUsers)
    {
        std::string str = fst;

        std::uint8_t byte0;
        std::uint8_t byte1;
        std::uint8_t byte2;
        std::uint8_t byte3;

        std::string tmp = fst.substr(0, fst.find('.'));
        if (!tmp.empty()) {
            byte0 = stoi(tmp);
            std::cout << byte0 << std::endl;
        } else {
            byte0 = 0;
        }
        fst = fst.erase(0, fst.find('.'));
        tmp = fst.substr(0, fst.find('.'));
        if (!tmp.empty()) {
            byte1 = stoi(tmp);
            std::cout << byte1 << std::endl;
        } else {
            byte1 = 0;
        }
        fst = fst.erase(0, fst.find('.'));
        tmp = fst.substr(0, fst.find('.'));
        if (!tmp.empty()) {
            byte2 = stoi(tmp);
            std::cout << byte2 << std::endl;
        } else {
            byte2 = 0;
        }
        fst = fst.erase(0, fst.find('.'));
        tmp = fst.substr(0, fst.find('.'));
        if (!tmp.empty()) {
            byte3 = stoi(tmp);
            std::cout << byte3 << std::endl;
        } else {
            byte3 = 0;
        }

        if (_udpSocket.send(p.getData(), p.getDataSize(), sf::IpAddress(byte0, byte1, byte2, byte3), snd) != sf::Socket::Status::Done) {
            log("UDP | Failed to send packet to client at port " + std::to_string(snd));
        }
        log("port : " + std::to_string(snd) + " ip : " + str);
    }
    log("Packet queued");
}

void Server::sendAll(sf::TcpSocket& socket, const void* data, const std::size_t size)
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

void Server::sendMessage(std::string message, unsigned int playerId)
{
    for (auto& user : _users)
    {
        if (user.getId() == playerId)
        {
            if (const auto socket = user.getSocket()) {
                sendAll(*socket, message.data(), message.size());
            }
            break;
        }
    }
}

void Server::start()
{
    _tcpClient = sf::TcpSocket();
    std::thread tcpThread(&Server::tcpThread, this);
    std::thread udpThread(&Server::udpThread, this);
    std::thread accepterThread(&Server::accepterThread, this);
    _game->run();
    tcpThread.join();
    udpThread.join();
    accepterThread.join();
}
