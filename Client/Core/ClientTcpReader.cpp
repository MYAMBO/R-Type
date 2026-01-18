/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ClientTcpReader.cpp
*/

#include "ClientTcpReader.hpp"

#include <cstdint>
#include <array>

#include "SFML/Audio/Music.hpp"

/**
 * Generates a login request message.
 *
 * @param data A string input used as placeholder or context for the request. It is currently ignored in the implementation.
 * @return A string containing the generated login request message.
 */
std::string ClientTcpReader::loginRequest(const std::string& data)
{
    (void)data;
    std::array<std::uint8_t, 1> buffer{};
    buffer[0] = 0x02;
    std::string message(
        reinterpret_cast<const char*>(buffer.data()),
        buffer.size()
    );
    return message;
}

/**
 * Generates the list with all level received from the client
 *
 * @param data A string containing the input data to be interpreted.
 * @return A Vector of string representing the result of interpreting the data.
 */
std::vector<std::string> ClientTcpReader::levelSelection(
    const std::string& data)
{
    std::vector<std::string> levelsNames;

    std::stringstream ss(data);
    std::string item;

    while (std::getline(ss, item, ',')) {
        levelsNames.push_back(item);
    }
    return levelsNames;
}

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
        case 2:
            return loginRequest(data);
        default:
            return {"undefined"};
    }
}
