/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ECSError.hpp
*/

#ifndef ECSERROR_HPP_
    #define ECSERROR_HPP_

    #include <string>
    #include <typeinfo>
    #include <exception>

/**
 * @brief A base class for ECS-related exceptions.
 */
class BaseECSException : public std::exception {
    public:
        virtual const char* what() const noexcept override {
            return "Generic ECS Error";
        }
};

/**
 * @brief A custom error, for component not found
 */
template <typename T>
class ECSComponentNotFoundException : public BaseECSException {
    public:
        ECSComponentNotFoundException() {
            _message = "[ECS Error] Component " + std::string(typeid(T).name()) + " not found";
        }
        
        [[nodiscard]] const char* what() const noexcept override {
            return _message.c_str();
        }
    private:
        std::string _message;
};

/**
 * @brief A custom error, for entity not found
 */
class ECSEntityNotFoundException : public std::exception {
    public:
        ECSEntityNotFoundException() = default;
        
        [[nodiscard]] const char* what() const noexcept override {
            return "[ECS Error] Entity not found";
        }
};

/**
 * @brief A custom error, for system not found
 */
template <typename T>
class ECSSystemNotFoundException : public std::exception {
    public:
        ECSSystemNotFoundException() {
            _message = "[ECS Error] System " + std::string(typeid(T).name()) + " not found";
        }
        
        [[nodiscard]] const char* what() const noexcept override {
            return _message.c_str();
        }

    private:
        std::string _message;
};

#endif