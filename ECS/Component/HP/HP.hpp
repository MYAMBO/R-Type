/*
** EPITECH PROJECT, 2025
** bs
** File description:
** HP
*/

#ifndef HP_HPP_
    #define HP_HPP_

#include "Component.hpp"

/**
 * @brief HP (Health Points) component to manage entity health.
 *
 * This component keeps track of the current and maximum health points
 * of an entity. It provides methods to retrieve and modify the health values.
*/
class HP : public Component {
    public:
        explicit HP(int maxHp);
        ~HP() override = default;

        [[nodiscard]] unsigned int getHP() const;
        void setHP(unsigned int hp);

        [[nodiscard]] unsigned int getMaxHP() const;
        void setMaxHP(unsigned int maxHp);

        [[nodiscard]] bool isAlive() const;
        void setAlive(bool alive);

    private:
        unsigned int _hp;
        unsigned int _maxHp;
        bool _isAlive;
};

#endif /* !HP_HPP_ */