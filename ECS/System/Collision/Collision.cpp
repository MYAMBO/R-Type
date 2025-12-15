/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Collision
*/

#include "Collision.hpp"



/**
 * @brief Updates the check of the collisions between entities.
 *
 * @param w The world containing the entities to be drawn.
 */
void Collision::update(const float &, World &w)
{
    const std::vector<std::shared_ptr<Entity>> entities = w.getAllEntitiesWithComponent<BoxCollider>();

    for (size_t i = 0; i < entities.size(); i++) {
        for (size_t j = i + 1; j < entities.size(); j++) {
            const std::shared_ptr<Entity> &a = entities[i];
            const std::shared_ptr<Entity> &b = entities[j];
            std::shared_ptr<BoxCollider> colA = a->getComponent<BoxCollider>();
            std::shared_ptr<BoxCollider>  colB = b->getComponent<BoxCollider>();
            std::shared_ptr<Position>  posA = a->getComponent<Position>();
            std::shared_ptr<Position>  posB = b->getComponent<Position>();
            if (!colA || !colB || !posA || !posB)
                continue;
            if (checkCollision(*colA, *posA, *colB, *posB)) {
                std::cout << "[Collision] Entity "
              << a->getId() << " <-> "
              << b->getId() << std::endl;
            }
        }
    }
}


/**
 * @brief check if two entities enter in collision.
 *
 * @param aB is the A entity BoxCollider
 * @param aP is the A entity Position
 * @param bB is the B entity BoxCollider
 * @param bP is the B entity Position
 *
 * @return true if a collision is detected and true else
 */
bool Collision::checkCollision(const BoxCollider &aB, const Position &aP,
    const BoxCollider &bB, const Position &bP)
{
    const sf::Vector2f aSize   = aB.getSize();
    const sf::Vector2f bSize   = bB.getSize();
    const sf::Vector2f aOffset = aB.getOffset();
    const sf::Vector2f bOffset = bB.getOffset();
    const float ax = aP.getX() + aOffset.x;
    const float ay = aP.getY() + aOffset.y;
    const float bx = bP.getX() + bOffset.x;
    const float by = bP.getY() + bOffset.y;

    if (ax < bx + bSize.x &&
        ax + aSize.x > bx &&
        ay < by + bSize.y &&
        ay + aSize.y > by)
        return true;
    return false;
}

