/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Scripts
*/

#ifndef SCRIPTS_HPP_
    #define SCRIPTS_HPP_

    #include "World.hpp"
    #include "Script.hpp"

void playerfire(size_t entityId, World &world);
void backgroundScrollScript(size_t entityId, World &world);
void changeSceneScript(int entityId, World& world);

#endif /* !SCRIPTS_HPP_ */