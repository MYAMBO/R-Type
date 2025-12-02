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
