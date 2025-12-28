/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Camera
*/
#include "CameraSys.hpp"

#include "Camera.hpp"
#include "Position.hpp"

/**
* @brief Update the camera of all entities if they have it in the world
* @param dt Delta time since last update
* @param w Reference to the world containing entities and components
*/
void CameraSys::update(const float &dt, World &w)
{
    (void)dt;
    for (auto &entity : w.getAllEntitiesWithComponent<Camera>()) {
        auto cameraComp = entity->getComponent<Camera>();
        if (!cameraComp)
            continue; 
        auto posComp = entity->getComponent<Position>();
        if (posComp)
            cameraComp->setPosition({posComp->getX(), posComp->getY()});
        w.getWindow()->setView(cameraComp->getView());
    }
}