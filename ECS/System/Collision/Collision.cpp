/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Collision
*/

#include "Collision.hpp"
#include "Tag.hpp"
#include "Damage.hpp"
#include "HP.hpp"




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
                handleCollisionDamage(a, b);
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


/**
 * @brief check and deal damage to entity.
 *
 * This function analyze which entity enter in collisions and apply damage.
 */
void Collision::handleCollisionDamage(const std::shared_ptr<Entity> &a,
                                      const std::shared_ptr<Entity> &b)
{
    auto tagA = a->getComponent<Tag>();
    auto tagB = b->getComponent<Tag>();

    if (!tagA || !tagB)
        return;
    std::string strTagA = tagA->getTag();
    std::string strTagB = tagB->getTag();
    if ((strTagA == "enemy" && strTagB == "player_bullet") ||
             (strTagB == "enemy" && strTagA == "player_bullet")) {
        auto target = (strTagA == "enemy") ? a : b;
        auto bullet = (strTagA == "player_bullet") ? a : b;
        applyDamage(bullet, target);
    }
    else if ((strTagA == "player" && strTagB == "enemy") ||
             (strTagB == "player" && strTagA == "enemy")) {
        applyDamage(a, b);
        applyDamage(b, a);
    }

    // to use later when player can be hit by enemy bullet

    // else if ((strTagA == "player" && strTagB == "enemy_bullet") ||
    //     (strTagB == "player" && strTagA == "enemy_bullet")) {
    //     auto target = (strTagA == "player") ? a : b;
    //     auto bullet = (strTagA == "enemy_bullet") ? a : b;
    //     applyDamage(bullet, target);
    // }
}

/**
 * @brief apply damage.
 *
 * This function apply damage and tell who enter in collision in the debug.
 */

void Collision::applyDamage(const std::shared_ptr<Entity> &attacker,
                            const std::shared_ptr<Entity> &target)
{
    auto damage = attacker->getComponent<Damage>();
    auto hp = target->getComponent<HP>();

    if (damage && hp) {
        hp->setHP(hp->getHP() - damage->getDamage());
        std::cout << "[Damage] Entity " << target->getId()
                  << " took " << damage->getDamage() << " damage ("
                  << hp->getHP() << " HP left)" << std::endl;
    }
}

