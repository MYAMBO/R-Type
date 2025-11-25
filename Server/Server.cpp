/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** server class declarations
*/

#include "Server.hpp"

Server::Server(int port)
{
    sf::TcpListener listener;
    if (listener.listen(port) != sf::Socket::Status::Done)
        throw InitServerException();

    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Status::Done)
        throw InitServerException();
}
