/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TcpReader.hpp
*/

#ifndef TCP_READER_HPP
    #define TCP_READER_HPP

    #include <vector>
    #include <string>

/**
 * @class TcpReader
 * @brief A class for interpreting TCP data and processing specific kinds of requests.
 *
 * The TcpReader class provides functionality to interpret received TCP data
 * and process specific commands or requests, such as login-related actions.
 */
class TcpReader
{
    public:
        TcpReader();
        ~TcpReader() = default;

        std::string InterpretData(const std::string& data);

    private:
        std::string loginRequest(const std::string& data);
        static std::vector<std::string> levelSelection(const std::string& data);
};

#endif //TCP_READER_HPP