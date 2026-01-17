/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** WorldFactory
*/

#ifndef WORLDFATORY_HPP_
    #define WORLDFATORY_HPP_

class Game;

class WorldFactory {
    public:
        WorldFactory(World& world);
        ~WorldFactory() = default;

        void createCamera();
        void createEnemy(float x, float y, int type, int entityId);
        void createPowerUp(float x, float y, int type, int entityId);
        void createPlayer(uint64_t playerId);
        void createEnemyBullet(size_t entityId, int x, int y);
        void createBullet(size_t entityId, int x, int y, int type);
        void createCompanion(uint64_t playerId);
        void createScraps(World &world, float x, float y);
        void createScrapUI(World &world, int index);
        void createLasersCompanion(uint64_t companionId, uint64_t playerId);
    private:
        World& _world;
};

#endif /* !WORLDFATORY_HPP_ */
