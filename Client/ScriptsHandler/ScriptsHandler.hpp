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

void dotScript(int entityId, World& world);
void kayuScript(int entityId, World& world);
void corpScript(int entityId, World& world);
void hpBarScript(int entityId, World& world);
void myamboScript(int entityId, World& world);
void playerScript(int entityId, World& world);
void manaBarScript(int entityId, World& world);
void playerfire(size_t entityId, World &world);
void kayuGlowScript(int entityId, World& world);
void corpGlowScript(int entityId, World& world);
void productionScript(int entityId, World& world);
void myamboGlowScript(int entityId, World& world);
void changeSceneScript(int entityId, World& world);
void productionGlowScript(int entityId, World& world);
void backgroundScrollScript(size_t entityId, World &world);

#endif /* !SCRIPTS_HPP_ */