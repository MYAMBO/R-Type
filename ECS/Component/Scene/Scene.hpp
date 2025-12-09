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
        Scene(int Scene = 1);
        ~Scene() override = default;

        [[nodiscard]] float getScene() const;

        void setScene(float Scene);

    private:
        int _Scene;
};

#endif /* !Scene_HPP_ */