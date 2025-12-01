/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Packet.cpp
*/

#include "Packet.hpp"

Packet::Packet(std::vector<uint8_t> data) : data(std::move(data)) {}

