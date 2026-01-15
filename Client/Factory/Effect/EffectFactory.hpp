/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** EffectFactory
*/

#ifndef EFFECTFACTORY_HPP_
    #define EFFECTFACTORY_HPP_

class Game;

class EffectFactory {
    public:
        EffectFactory(World& world);
        ~EffectFactory() = default;

        void createKayu();
        void createMyambo();
        void createCredits();
        static void createSparks(World &world, float x, float y, int amount);
    private:
        World& _world;
};

#endif /* !EFFECTFACTORY_HPP_ */