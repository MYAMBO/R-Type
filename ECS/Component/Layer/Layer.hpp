/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Layer
*/

#ifndef R_TYPE_LAYER_HPP
    #define R_TYPE_LAYER_HPP

#include "Component.hpp"

/**
 * @brief Layer component to define rendering order of entities.
 *
 * Each entity with a Layer component can be assigned a layer ID,
 * which determines its rendering order relative to other entities.
 * Entities with lower layer IDs are rendered before those with higher IDs.
*/
class Layer : public Component {
    public:

        Layer(int id);
        ~Layer() override = default;

        void setLayerId(int id);
        [[nodiscard]] int getLayerId() const;

    private:
        int _id;
};

#endif //R_TYPE_LAYER_HPP
