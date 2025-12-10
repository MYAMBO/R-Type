/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CustomError.hpp
*/

#ifndef R_TYPE_CUSTOMERROR_HPP
    #define R_TYPE_CUSTOMERROR_HPP


/**
 * @brief A custom error, for full packet
 */
class PacketFullError : public std::exception
{
    public:
        PacketFullError();
    private:
        [[nodiscard]] const char* what() const noexcept override {
            return "Packet data is full";
        }
};


/**
 * @brief A custom error, for missing parameter
 */
class MissingPacketParameterError : public std::exception
{
    public:
        MissingPacketParameterError();
    private:
        [[nodiscard]] const char* what() const noexcept override {
            return "Packet: missing required parameter";
        }
};

#endif //R_TYPE_CUSTOMERROR_HPP