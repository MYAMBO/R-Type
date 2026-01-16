/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TcpReader.hpp
*/

#ifndef TCP_READER_HPP
    #define TCP_READER_HPP

    #include <string>

class TcpReader
{
    public:
        TcpReader();
        ~TcpReader() = default;

        std::string InterpretData(const std::string& data);

    private:
        std::string loginRequest(const std::string& data);
};

#endif //TCP_READER_HPP