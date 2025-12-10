/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** MyString.cpp
*/

#include "MyString.hpp"

#include <utility>

/**
 * @brief Construct a new MyString
*/
MyString::MyString(std::string s) : _data(std::move(s)){};

/**
 * @brief A SubStr who consume the char
*/
std::string MyString::mySubStr(const size_t pos, const size_t n)
{
    std::string output = _data.substr(pos, n);
    _data.erase(pos, n);
    return output;
}

/**
 * @brief A wrapped SubStr from std::string
 */
std::string MyString::substr(const size_t pos, const size_t n) const
{
    return _data.substr(pos, n);
}

/**
 * @brief A wrapped size from std::string
 */
size_t MyString::size() const
{
    return _data.size();
}

/**
 * @brief A wrapped c_str from std::string
 */
const char* MyString::c_str() const
{
    return _data.c_str();
}

/**
 * @brief A wrapped operator from std::string
 */
MyString::operator std::string() const
{
    { return _data; }
}


