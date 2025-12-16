/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** IGameNetwork.hpp
*/

#ifndef I_GAME_NETWORK_HPP
#define I_GAME_NETWORK_HPP

#include "Packet.hpp"

struct IGameNetwork
{
    virtual ~IGameNetwork() = default;

    virtual void sendPacket(const Packet& packet) = 0;
};

#endif
