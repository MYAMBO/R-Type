/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ClientTcpReader.cpp
*/

#include "ClientTcpReader.hpp"

#include <cstdint>
#include <array>
#include <utility>

#include "SFML/Audio/Music.hpp"

ClientTcpReader::ClientTcpReader(std::shared_ptr<Game> game) : _game(std::move(game)) {}

/**
 * Interprets incoming data and processes it based on its type.
 *
 * @param data A string containing the input data to be interpreted. The first character is used to determine the type of operation.
 * @return A string representing the result of interpreting the data. Returns a login request string if the type matches, or "undefined" if no valid type is identified.
 */
std::string ClientTcpReader::InterpretData(const std::string& data)
{
    if (data.empty())
        return {};

    switch (data.at(0)) {
        case 6:
            return {"Mode Confirmed"};
        default:
            return {"undefined"};
    }
}
