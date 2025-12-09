/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Entity
*/

#include "Entity.hpp"

/**
 * @brief Constructs a new Entity object with a unique ID.
*/
Entity::Entity()
{
    static int id = 0;
    _id = id++;
}

/**
 * @brief Return the id of the entity
 */
std::size_t Entity::getId(void) const
{
    return _id;
}