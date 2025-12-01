/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Packet.hpp
*/

#ifndef R_TYPE_PACKET_HPP
#define R_TYPE_PACKET_HPP
#include <cstdint>
#include <string>
#include <vector>


class Packet
{
    public:
        Packet() = default;
        explicit Packet(std::vector<uint8_t> data);

        ~Packet() = default;

        void Login(std::string);
    private:
        std::vector<uint8_t> data;
};


#endif //R_TYPE_PACKET_HPP