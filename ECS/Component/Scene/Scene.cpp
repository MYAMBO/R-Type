/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Scene
*/

#include "Scene.hpp"

/**
 * @brief Constructs a Scene component with the specified Scene value.
 * @param Scene The Scene value of the entity.
*/
Scene::Scene(int scene)
        : _scene(scene)
{
}

/**
 * @brief Gets the Scene value of the entity.
 * @return The Scene value of the entity.
*/
float Scene::getScene()
{
    return _scene;
}

/**
 * @brief Sets the Scene value of the entity.
 * @param Scene The new Scene value of the entity.
*/
void Scene::setScene(float scene)
{
    _scene = scene;
}