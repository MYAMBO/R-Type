/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** MyString.cpp
*/

#include "MyString.hpp"

#include <utility>

MyString::MyString(std::string s) : _data(std::move(s)){};

std::string MyString::mySubStr(const size_t pos, const size_t n)
{
    std::string output = _data.substr(pos, n);
    _data.erase(pos, n);
    return output;
}

std::string MyString::substr(const size_t pos, const size_t n) const
{
    return _data.substr(pos, n);
}

size_t MyString::size() const
{
    return _data.size();
}

const char* MyString::c_str() const
{
    return _data.c_str();
}

MyString::operator std::string() const
{
    { return _data; }
}


