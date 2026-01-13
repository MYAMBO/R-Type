/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** ToolsFactory
*/

#ifndef TOOLSFACTORY_HPP_
    #define TOOLSFACTORY_HPP_

class Game;

class ToolsFactory {
    public:
        ToolsFactory(World& world);
        ~ToolsFactory() = default;

        void createGameTools();
    private:
        World& _world;
};

#endif /* !TOOLSFACTORY_HPP_ */