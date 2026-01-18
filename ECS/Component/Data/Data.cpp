/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Data
*/

#include <string>

#include "Data.hpp"

/**
 * @brief Constructs a new Data component with specified data map.
 * @param data The initial key-value data map.
*/
Data::Data(std::map<std::string, std::string> data)
    : _data(data)
{
}

/**
 * @brief Gets the entire data map.
 * @return The key-value data map.
*/
std::map<std::string, std::string> Data::getDataSet() const
{
    return _data;
}

/**
 * @brief Gets the value associated with a specific key.
 * @param key The key to look up.
 * @return The corresponding value, or an empty string if the key does not exist.
*/
std::string Data::getData(const std::string& key) const
{
    auto it = _data.find(key);
    if (it != _data.end()) {
        return it->second;
    }
    return "";
}

/**
 * @brief Checks if a specific key exists in the data map.
 * @param key The key to check.
 * @return true if the key exists, false otherwise.
*/
bool Data::hasData(const std::string& key) const
{
    return _data.find(key) != _data.end();
}

/**
 * @brief Sets the entire data map.
 * @param data The new key-value data map.
*/
void Data::setDataSet(const std::map<std::string, std::string>& data)
{
    _data = data;
}

/**
 * @brief Sets a key-value pair in the data map.
 * @param key The key to set.
 * @param value The value to associate with the key.
*/
void Data::setData(const std::string& key, const std::string& value)
{
    _data[key] = value;
}
