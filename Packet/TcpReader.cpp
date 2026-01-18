/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TcpReader.cpp
*/

#include "TcpReader.hpp"
#include <cstdint>
#include <array>

#include "SFML/Audio/Music.hpp"

/**
 * @brief Construct a TcpReader
 * @param game Pointer to the Server-side game
 */
TcpReader::TcpReader(std::shared_ptr<ServerGame> game)
{
    _game = std::move(game);
}

/**
 * Generates a login request message.
 *
 * @param data A string input used as placeholder or context for the request. It is currently ignored in the implementation.
 * @return A string containing the generated login request message.
 */
std::string TcpReader::loginRequest(const std::string& data)
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
 * Interprets incoming data and processes it based on its type.
 *
 * @param data A string containing the input data to be interpreted. The first character is used to determine the type of operation.
 * @return A string representing the result of interpreting the data. Returns a login request string if the type matches, or "undefined" if no valid type is identified.
 */
std::string TcpReader::InterpretData(const std::string& data)
{
    if (data.empty())
        return {};

    std::cout << "TCP data : " << data << std::endl;
    switch (data.at(0)) {
        case 2:
            return loginRequest(data);
        case 6 : {
            if (data.size() < 2)
                return {};
            int value = static_cast<unsigned char>(data.at(1));
            _game->setMode(static_cast<Mode>(value));
            return {"Mode Setted"};
        }
        default:
            return {};
    }
}
