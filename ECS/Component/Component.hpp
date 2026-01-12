/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
    #define COMPONENT_HPP_

#include "iostream"

/** 
 * @brief Base class for all components in the ECS architecture.
 *
 * Components are used to store data for entities in the ECS (Entity-Component-System) pattern.
 * This base class provides a common interface for all component types.
 */
class Component {
    public:
        Component() = default;
        virtual ~Component() = default;
};

#endif /* !COMPONENT_HPP_ */