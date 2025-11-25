/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** server class
*/

#pragma once

#include "SFML/Network.hpp"

class Server
{
    public:
        Server(int port);
        ~Server() = default;
        //void start();
    private:

    class InitServerException : public std::exception
    {
        const char* what() const noexcept override
        {
            return "Unable to initialize server";
        }
    };
};