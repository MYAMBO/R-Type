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
Entity::Entity(int side)
    : _side(side)
{
    static int id = 0;
    static int clientId = 0;
    if (side == 0) {
        _id = id;
        id++;
    } else {
        _clientId = clientId;
        clientId--;
    }
}

/**
 * @brief Return the id of the entity
 */
int Entity::getId(void) const
{
    if (_side == SERVERSIDE)
        return static_cast<int>(_id);
    return _clientId;
}