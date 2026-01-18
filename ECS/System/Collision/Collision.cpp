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
#include "Packet.hpp"
#include "Action.hpp"


Collision::Collision(IGameNetwork& network) : _network(network)
{
}


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
            auto colA = a->getComponent<BoxCollider>();
            auto colB = b->getComponent<BoxCollider>();
            auto posA = a->getComponent<Position>();
            auto posB = b->getComponent<Position>();

            if (!colA || !colB || !posA || !posB)
                continue;

            if (checkCollision(*colA, *posA, *colB, *posB))
                handleCollisionDamage(a, b);
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
        applyDamage(target, bullet);
    }
    else if ((strTagA == "player" && strTagB == "enemy") ||
             (strTagB == "player" && strTagA == "enemy")) {
        applyDamage(a, b);
        applyDamage(b, a);
    }

    else if ((strTagA == "player" && strTagB == "enemy_bullet") ||
        (strTagB == "player" && strTagA == "enemy_bullet")) {
        auto target = (strTagA == "player") ? a : b;
        auto bullet = (strTagA == "enemy_bullet") ? a : b;
        applyDamage(bullet, target);
        applyDamage(target, bullet);
    }
    else if ((strTagA == "player_bullet" && strTagB == "enemy_bullet") ||
        (strTagB == "player_bullet" && strTagA == "enemy_bullet")) {
        auto target = (strTagA == "player_bullet") ? a : b;
        auto bullet = (strTagA == "enemy_bullet") ? a : b;
        applyDamage(bullet, target);
        applyDamage(target, bullet);
        auto hpComp1 = bullet->getComponent<HP>();
        auto hpComp2 = target->getComponent<HP>();
        if (hpComp1)
            hpComp1->setHP(0);
        if (hpComp2)
            hpComp2->setHP(0);
    }
    else if ((strTagA == "player" && strTagB == "heal") ||
             (strTagB == "player" && strTagA == "heal")) {
        auto player = (strTagA == "player") ? a : b;
        auto heal = (strTagA == "heal") ? a : b;
        applyHeal(player, heal);
    }
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
    auto targetTag = target->getComponent<Tag>();

    if (damage && hp) {
        int oldHp = hp->getHP();
        int newHp = oldHp - damage->getDamage();
        if (newHp < 0)
            newHp = 0;
        hp->setHP(newHp);
        if (targetTag && targetTag->getTag() == "player") {
            printf("[Collision] Player entity %d took %d damage, HP: %d -> %d\n",
                target->getId(), damage->getDamage(), oldHp, newHp);
            Packet packet;
            packet.action(target->getId(), HEAL, newHp);
            _network.sendPacket(packet);
        }
    }
}

void Collision::applyHeal(const std::shared_ptr<Entity> &player,
    const std::shared_ptr<Entity> &heal)
{
    auto hp = player->getComponent<HP>();
    if (!hp)
        return;
    unsigned int currentHp = hp->getHP();
    unsigned int maxHp = hp->getMaxHP();
    unsigned int healAmount = 20;
    unsigned int newHp = std::min(currentHp + healAmount, maxHp);
    hp->setHP(newHp);
    printf("[Collision] Player entity %d healed for %d, HP: %d -> %d\n",
        player->getId(), newHp - currentHp, currentHp, newHp);
    Packet packet;
    packet.action(player->getId(), HEAL, newHp);
    _network.sendPacket(packet);

    auto powerupHp = heal->getComponent<HP>();
    if (powerupHp)
        powerupHp->setHP(0);
}

