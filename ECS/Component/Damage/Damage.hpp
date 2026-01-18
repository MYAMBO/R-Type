/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Damage
*/


#ifndef R_TYPE_DAMAGE_HPP
    #define R_TYPE_DAMAGE_HPP

#include "Component.hpp"

/**
 * @brief Damage component to define if entities can deals damage.
 *
 * Each entity with a Damage component can deal damage to the other and
 * in agreement with HP component, it can reduce the number of HP of an entity.
*/
class Damage : public Component {

    public:
        explicit Damage(int damage);
        ~Damage() override = default;

        void setDamage(const int damage);
        [[nodiscard]] int getDamage() const;

    private:
        int _damage;
};

#endif //R_TYPE_DAMAGE_HPP
