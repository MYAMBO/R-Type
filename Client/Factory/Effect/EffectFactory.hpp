/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** EffectFactory
*/

#ifndef EFFECTFACTORY_HPP_
    #define EFFECTFACTORY_HPP_

class Game;
class World;
enum class SceneType;

class EffectFactory {
    public:
        EffectFactory(World& world);
        ~EffectFactory() = default;

        void createKayu();
        void createMyambo();
        void createCredits();
        static void createSparks(World &world, float x, float y, int amount, SceneType scene, int lifeTime = 300);
    private:
        World& _world;
};

#endif /* !EFFECTFACTORY_HPP_ */