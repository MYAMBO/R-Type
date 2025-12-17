/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Network
*/

#ifndef R_TYPE_NETWORK_H
#define R_TYPE_NETWORK_H

#include <mutex>
#include <thread>
#include <utility>
#include <Packet.hpp>
#include <ClientPacketreader.hpp>

#include "IGameNetwork.hpp"

class Network : public IGameNetwork {
    public:
        Network();
        ~Network() override = default;

        void initClient();
        void start();
        void parse(int ac, char** av);
        void udpThread();
        void tcpThread();
        void sendMessage(const std::string &message);
        void log(const std::string& message) const;
        void sendPacket(Packet& packet) override;
        void setGameToPacketReader();
        static void sendAll(sf::TcpSocket& socket, const void* data, std::size_t size);

        class InitClientException : public std::exception
        {
        public:
            explicit InitClientException(std::string message = "")
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
        void getIpAdress(std::string option);
        sf::UdpSocket _udpSocket;
        sf::TcpSocket _tcpClient;
        sf::IpAddress _ip;
        std::thread _udpThread;
        long _tcpPort;
        long _udpPort;
        bool _debugMode;
        std::mutex _mutex;
        std::shared_ptr<Game> _game;
        ClientPacketreader _packetReader;
};


#endif //R_TYPE_NETWORK_H