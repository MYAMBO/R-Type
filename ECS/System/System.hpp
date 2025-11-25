/*
** EPITECH PROJECT, 2025
** bs
** File description:
** System
*/

#ifndef SYSTEM_HPP_
    #define SYSTEM_HPP_

class World;

class System {
    public:
        System() = default;
        virtual ~System() = default;

        virtual void update(const float& dt, World &w) = 0;
    private:
};

#endif /* !SYSTEM_HPP_ */