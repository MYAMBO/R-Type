/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Entity
*/

#include "Entity.hpp"

Entity::Entity()
{
    static int id = 0;
    _id = id++;
}
