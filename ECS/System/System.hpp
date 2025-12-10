/*
** EPITECH PROJECT, 2025
** bs
** File description:
** System
*/

#ifndef SYSTEM_HPP_
    #define SYSTEM_HPP_

class World;

/**
 * @brief Base class for all systems in the ECS architecture.
 *
 * Systems are responsible for processing entities that possess specific components.
 * This base class provides a common interface for all system types.
 */
class System {
    public:
        System() = default;
        virtual ~System() = default;

        virtual void update(const float& dt, World &w) = 0;
    private:
};

#endif /* !SYSTEM_HPP_ */