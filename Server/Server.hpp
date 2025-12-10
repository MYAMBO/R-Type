/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Server.hpp
*/

#pragma once

#include "SFML/Network.hpp"

class Server
{
public:
    Server();
    ~Server() = default;
    void initServer();
    void start();
    void parse(int ac, char **av);
    void log(const std::string& message) const;
    void udpThread();
    void tcpThread();

    class InitServerException : public std::exception
    {
        const char* what() const noexcept override
        {
            return "Unable to initialize server";
        }
    };
};