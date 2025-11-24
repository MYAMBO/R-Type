/*
** EPITECH PROJECT, 2025
** bs
** File description:
** HP
*/

#pragma once

#include "Component.hpp"

class HP : public Component {
    public:
        HP(int maxHp);
        virtual ~HP() = default;

        unsigned int getHP() const;
        void setHP(unsigned int hp);
    private:
        unsigned int _hp;
        unsigned int _maxHp;
};
