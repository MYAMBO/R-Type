/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Entity.cpp
*/

#include "Entity.hpp"
#include <random>
#include <algorithm>

/**
 * @brief Constructs a new Entity object with a unique 16-byte UUID.
*/
Entity::Entity(uint32_t id)
{
    if (id != 0) {
        //printf("Assigned Entity ID: %d\n", id);
        _id = id;
        return;
    }
    static std::random_device rd;
    static std::mt19937_64 gen(rd());

    static std::uniform_int_distribution<uint32_t> dis(0, 0x00FFFFFF);

    uint32_t randomPart = dis(gen);

    _id = randomPart;
    //printf("Generated Entity ID: %d\n", _id);
}

/**
 * @brief Return the unique ID of the entity
 */
uint32_t Entity::getId(void) const
{
    return _id;
}