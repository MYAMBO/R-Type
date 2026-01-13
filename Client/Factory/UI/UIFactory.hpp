/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** UIFactory
*/

#ifndef UIFACTORY_HPP_
    #define UIFACTORY_HPP_

class Game;

class UIFactory {
    public:
        UIFactory(World& world);
        ~UIFactory() = default;

        void createMenu();
        void createOptionsMenu();
        void createLoadingScreen();

    private:
        World& _world;
};

#endif /* !UIFACTORY_HPP_ */