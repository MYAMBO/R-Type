/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Script
*/

#include "Script.hpp"

/**
 * @brief Constructs a Script component with the specified script function.
 * @param script The script function to be associated with the entity.
*/
Script::Script(std::function<void(int entityId, World &world)> script)
        : _script(script)
{
}

/**
 * @brief Gets the script function associated with the entity.
 * @return The script function.
*/
std::function<void(int entityId, World &world)> Script::getScript() const
{
    return _script;
}

/**
 * @brief Sets the script function associated with the entity.
 * @param script The new script function.
*/
void Script::setScript(std::function<void(int entityId, World &world)> script)
{
    _script = script;
}