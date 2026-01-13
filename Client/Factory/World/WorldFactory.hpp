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
        void createBackground(sf::RenderWindow& window);
        void createEnemy(float x, float y, int type, int entityId);
        void createPlayer(uint64_t playerId);
        void createEnemyBullet(size_t entityId, int x, int y);
        void createBullet(size_t entityId, int x, int y, int type);
    private:
        World& _world;
};

#endif /* !WORLDFATORY_HPP_ */
