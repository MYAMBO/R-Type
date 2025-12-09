/*
** EPITECH PROJECT, 2025
** *
** File description:
** Scene
*/

#ifndef Scene_HPP_
    #define Scene_HPP_

#include "Component.hpp"

/**
 * @brief Scene component to define the Scene of an entity.
 *
 * This component holds the Scene factor of an entity.
 * It provides methods to retrieve and modify the Scene value.
*/
class Scene : public Component {
    public:
        explicit Scene(int Scene = 1);
        ~Scene() override = default;

        [[nodiscard]] int getScene() const;

        void setScene(int Scene);

    private:
        int _scene;
};

#endif /* !Scene_HPP_ */