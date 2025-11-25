/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Layer
*/

#ifndef R_TYPE_LAYER_HPP
    #define R_TYPE_LAYER_HPP

#include "../Component.hpp"

class Layer : public Component {
    public:

        Layer(int id);
        virtual ~Layer() = default;

        void setLayerId(const int id);
        [[nodiscard]] int getLayerId() const;

    private:
        int _id;
};

#endif //R_TYPE_LAYER_HPP
