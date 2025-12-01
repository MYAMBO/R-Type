/*
** EPITECH PROJECT, 2025
** bs
** File description:
** HP
*/

#ifndef HP_HPP_
    #define HP_HPP_

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

#endif /* !HP_HPP_ */