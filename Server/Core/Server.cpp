/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Server.cpp
*/

#include "Server.hpp"

#include <algorithm>
#include <cstring>

#include "TcpReader.hpp"

/**
 * @brief Represents a server that handles client connections and processes requests.
 *
 * Provides functionality to initialize, manage connections, handle client requests,
 * and perform related server operations. This class acts as the core component
 * for running a server and executing defined tasks for connected clients.
 *
 * @return None
 */
Server::Server() : _tcpReader(nullptr)
{
    _tick = 0;
    _tcpPort = -1;
    _udpPort = -1;
    _debugMode = false;
    _game = std::make_shared<ServerGame>(*this, _tick, _ackPackets, _users);
    _packetReader = Packetreader(sf::Packet(), _game);
    _tcpReader = TcpReader(_game);
}

/**
 * @brief Parses the command-line arguments to configure the server.
 *
 * Processes the provided command-line arguments to set the TCP port, UDP port,
 * and debug mode for the server. If invalid arguments are provided or required
 * options are missing, appropriate exceptions are thrown.
 *
 * @param ac The number of command-line arguments.
 * @param av The array of command-line arguments.
 *
 * @throws InitServerException If the TCP port or UDP port is not specified or invalid.
 */
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

/**
 * @brief Initializes the server by setting up TCP and UDP listeners.
 *
 * Creates and configures a TCP listener to listen on the specified
 * port for incoming connections. Also sets up a UDP socket to bind to
 * a designated port for handling UDP communication.
 *
 * Logs the status of each listener upon successful initialization.
 * If setting up either the TCP or UDP listeners fails, throws
 * an InitServerException.
 *
 * @throws InitServerException If TCP or UDP listener initialization fails.
 */
auto Server::initServer() -> void
{
    _tcpListener = sf::TcpListener();
    _udpSocket = sf::UdpSocket();

    if (_tcpListener.listen(_tcpPort, sf::IpAddress::Any) != sf::Socket::Status::Done)
        throw InitServerException();
    log("TCP server listening on port " + std::to_string(_tcpPort));
    if (_udpSocket.bind(_udpPort, sf::IpAddress::Any) != sf::Socket::Status::Done)
        throw InitServerException();
    log("UDP server listening on port " + std::to_string(_udpPort));

}

/**
 * @brief Logs a message with a timestamp if debug mode is enabled.
 *
 * Outputs the provided message to the standard output stream, preceded by
 * the current timestamp, in the format "[YYYY-MM-DD HH:MM:SS] message".
 * This logging is conditional on the `_debugMode` flag being enabled.
 *
 * @param message The string message to be logged.
 */
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

/**
 * @brief Manages the reception and processing of incoming UDP packets in a separate thread.
 *
 * This function handles continuous listening on the UDP socket for incoming data packets.
 * Upon receiving a packet, it extracts the sender's IP address and port, processes the data,
 * and attempts to interpret it using the packet reader.
 *
 * Logs errors if the interpretation of the packet fails due to any exception. The sender's
 * details are stored and maintained to track unique clients. If a sender is not currently
 * recorded in the UDP users list, it is added. Each successful packet reception, along with
 * relevant metadata (size, sender address, port), is logged.
 *
 * The function ensures robust handling of non-successful packet reception by introducing
 * a delay and retrying until data is successfully received. It operates indefinitely unless
 * externally interrupted.
 */
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

        _packetReader.addPacket(p);
        try
        {
            _packetReader.interpretPacket();
            u_int32_t ackNb = _packetReader.getHeader().ack;
            _mutex.lock();
            for (auto tmp : _users)
            {
                if (std::find(tmp._ackList.begin(), tmp._ackList.end(), ackNb) != tmp._ackList.end()) {
                    tmp._ackList.erase(std::remove(tmp._ackList.begin(), tmp._ackList.end(), ackNb), tmp._ackList.end());
                }
            }
            _mutex.unlock();

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
        // log("UDP | Received " + std::to_string(p.getDataSize()) + " bytes from " + sender.value().toString() + " on port " + std::to_string(rport));
    }
}

/**
 * @brief Manages incoming TCP messages from connected clients in a separate thread.
 *
 * This function processes incoming TCP messages from all currently connected clients.
 * It continuously checks for data reception from connected client sockets in a thread-safe manner.
 * Logs received data along with client details (ID, port, IP) if data is successfully received.
 * If no data is received from any client during an iteration, the thread waits briefly before retrying.
 *
 * The function runs indefinitely and handles concurrent access to the list of connected users using a mutex.
 */
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
            std::string message;

            while (true)
            {
                data.fill(0);
                sf::Socket::Status status = tmp.getSocket()->receive(data.data(), data.size(), received);
                if (status == sf::Socket::Status::Disconnected)
                {
                    _mutex.lock();
                    _users.erase(std::remove_if(_users.begin(), _users.end(), [&](const auto& user) { return user.getId() == tmp.getId(); }), _users.end());
                    log("TCP | Client " + std::to_string(tmp.getId()) + " disconnected");
                    _mutex.unlock();
                    break;
                }
                if ((status != sf::Socket::Status::Done && message.empty()))
                    break;

                if (received != 0)
                {
                    dataReceived = true;
                    message += std::string(data.data(), received);

                    log("TCP | Received " + std::to_string(received) + " bytes with value " + std::string(data.data(), received) + " from client " + std::to_string(tmp.getId()) + " with port " + std::to_string(tmp.getPort()) + " with ip " + tmp.getIp());

                    if ((received < data.size() || status != sf::Socket::Status::Done) && !message.empty())
                    {
                        if (!message.empty()) {
                            if (const unsigned char opcode = static_cast<unsigned char>(message.at(0)); opcode == 0x0E) {
                                if (_game) {
                                    _game->handlePlayerReady(tmp.getId());
                                    log("TCP | Player ready: " + std::to_string(tmp.getId()));
                                }
                                message.clear();
                                break;
                            }
                        }
                        std::string messageResponse = _tcpReader.InterpretData(message);
                        _mutex.lock();
                        sendMessage(messageResponse, tmp.getId());
                        _mutex.unlock();
                        message.clear();
                        log("sent");
                        break;
                    }
                }
            }
        }

        if (!dataReceived)
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

/**
 * @brief Continuously accepts incoming TCP client connections and initializes them for server communication.
 *
 * This method runs in a dedicated thread and listens for incoming TCP client connection requests.
 * Upon successfully accepting a connection, it extracts the client's port and IP address for logging
 * and further processing. The connected socket is then set to non-blocking mode.
 *
 * A buffer is prepared to store metadata, including a unique player ID and the server's UDP port.
 * The player ID is generated and assigned to the new client while ensuring thread safety
 * with a mutex-protected list of connected users. The buffer is updated with this information
 * before being sent as an initial message to the new client.
 *
 * The method indefinitely loops to handle new incoming connections and ensures all
 * required initialization for newly connected clients is handled properly.
 */
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

        std::lock_guard<std::mutex> lock(_mutex);
        _users.emplace_back(port, ip, std::make_shared<sf::TcpSocket>(std::move(_tcpClient)));
        playerId = _users.back().getId();
        buffer[1] = static_cast<std::uint8_t>(playerId);

        std::uint32_t udpPort = htonl(_udpPort);
        std::memcpy(&buffer[2], &udpPort, sizeof(udpPort));

        std::string message(
            reinterpret_cast<const char*>(buffer.data()),
            buffer.size()
        );

        sendMessage(message, playerId);
    }
}

/**
 * @brief Sends a UDP packet to all connected clients.
 *
 * This method constructs the packet with initial parameters and retrieves the
 * packet data. It iterates through the connected UDP users, determines the IP
 * address from the user string by splitting it into four bytes, and sends
 * the packet to each client using `sf::UdpSocket::send`. In case of a failure
 * to send the packet, it logs an error for the respective client. Once the
 * process concludes, it logs that the packet was queued successfully.
 *
 * @param packet The Packet object to be sent, which is configured and serialized
 *               before sending to clients.
 */
void Server::sendPacket(Packet& packet)
{
    packet.setId(0).setAck(0).setPacketNbr(1).setTotalPacketNbr(1);
    const sf::Packet p = packet.getPacket();

    for (auto &[fst, snd] : _udpUsers)
    {
        std::optional<sf::IpAddress> optIp = sf::IpAddress::resolve(fst);

        if (!optIp.has_value() || _udpSocket.send(p.getData(), p.getDataSize(), optIp.value(), snd) != sf::Socket::Status::Done) {
            log("UDP | Failed to send packet to client at port " + std::to_string(snd));
        }
        // log("port : " + std::to_string(snd) + " ip : " + optIp.value().toString());
    }
    // log("Packet queued");
}

/**
 * @brief Sends the entire specified data buffer over a TCP socket.
 *
 * This function ensures that all data in the given buffer is sent over the specified TCP socket.
 * It handles partial sends by repeatedly sending the remaining data until the entire buffer is transmitted.
 * If the transmission fails at any point, it throws a runtime exception.
 *
 * @param socket The TCP socket over which the data will be sent.
 * @param data A pointer to the data buffer to be sent.
 * @param size The size of the data buffer in bytes.
 * @throws std::runtime_error If the send operation fails for any reason.
 */
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

/**
 * @brief Sends a message to a specific player identified by their ID.
 *
 * This function iterates through the list of connected users to locate the user with the given player ID.
 * If the user is found and their associated socket is valid, the message is sent using the specified socket.
 * The operation stops as soon as the intended player is located.
 *
 * @param message The message to be sent to the player.
 * @param playerId The unique identifier of the player to whom the message is sent.
 */
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

/**
 * @brief Initiates server operation by starting network communication threads and game logic.
 *
 * This function sets up required threads for handling different aspects of the server:
 * - Manages incoming TCP connections and communication through a dedicated TCP handling thread.
 * - Oversees UDP communication using a separate UDP handling thread.
 * - Handles new client connections through an acceptor thread.
 *
 * Additionally, the function initiates the game's main logic loop, which operates sequentially with the network threads.
 * All threads are joined at the end to ensure orderly termination of the server's operation.
 */
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
