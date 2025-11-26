/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Velocity
*/


#ifndef R_TYPE_VELOCITY_HPP
    #define R_TYPE_VELOCITY_HPP

#include "../Component.hpp"

class Velocity : public Component {
    public:
        Velocity(float velocity);
        virtual ~Velocity() = default;

    [[nodiscard]] float getVelocity() const;

    void setVelocity(float velocity);

    private:
        float _velocity;

};

#endif //R_TYPE_VELOCITY_HPP
