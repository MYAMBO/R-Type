/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Group
*/

#include "Group.hpp"

/**
 * @brief Constructs a new Group component with specified ID.
 * @param id The group ID.
*/
Group::Group(size_t id) : _id(id)
{
}

/**
 * @brief Gets the ID of the group.
 * @return The group ID.
*/
size_t Group::getId() const
{
    return _id;
}

/**
 * @brief Sets a new ID for the group.
 * @param id The new group ID.
*/
void Group::setId(size_t id)
{
    _id = id;
}