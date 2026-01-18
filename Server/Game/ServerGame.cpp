/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#include <algorithm>
#include <cmath>

#include "HP.hpp"
#include "Tag.hpp"
#include "Server.hpp"
#include "Packet.hpp"
#include "Script.hpp"
#include "Velocity.hpp"
#include "Movement.hpp"
#include "Position.hpp"
#include "ScriptsSys.hpp"
#include "ServerGame.hpp"
#include "GameHelper.hpp"
#include "BoxCollider.hpp"
#include "LevelLoader.hpp"
#include "DeathSys.hpp"
#include "Damage.hpp"
#include "Collision.hpp"
#include "Action.hpp"
#include "Data.hpp"

static auto getAckId() -> u_int32_t
{
    static u_int32_t id = 0;
    return ++id;
}

/**
 * @brief Constructs a new Game object.
 *
 * Initializes the game.
 */
ServerGame::ServerGame(IGameNetwork& network, u_int32_t &tick, std::vector<std::pair<Packet, u_int32_t>> &ackPackets, std::vector<User> &users) :
_tick(tick), _network(network), _ackPackets(ackPackets), _users(users)
{
    _world.addSystem<ScriptsSys>();
    _world.addSystem<Collision>(_network);
    _world.addSystem<DeathSys>(_network);
    _world.addSystem<Movement>();
    _world.setDeltaTime(1.f);
    _packet.setId(0).setAck(0).setPacketNbr(1).setTotalPacketNbr(1);
}

/**
 * @brief Runs the main game loop.
 *
 * This function initializes the game world, creates entities,
 * and handles the main event loop.
 */
void ServerGame::run()
{
    const auto tickRate = std::chrono::microseconds(1000000 / 30);

    _world.manageSystems();

    while (true) {
        auto start = std::chrono::steady_clock::now();

        // Gestion des vagues
        // if (_gameStarted && _waveTimer.getElapsedTime().asSeconds() >= 20.f) {
        //    createWave();
        //    _waveTimer.restart();
        // }
        _world.manageSystems();
        checkDeaths();
        _ackPackets.erase(
            std::remove_if(_ackPackets.begin(), _ackPackets.end(),
                [this](const std::pair<Packet, u_int32_t>& tmpPacket) {
                    return tmpPacket.second + 1500 < _tick;
                }),
            _ackPackets.end()
        );

        for (const auto& tmp : _users)
        {
            if (_ackPackets.empty())
                break;
            if (tmp._ackList.empty())
                continue;
            for (auto tmpAck : tmp._ackList)
            {
                for (auto [fst, snd] : _ackPackets)
                {
                    if (snd == tmpAck && snd + 500 < _tick)
                        _network.sendPacket(fst);
                }
            }
        }
        checkGameEnd();
        if (_packet.getPacket().getDataSize() != 12) {
            _network.sendPacket(_packet);
            _packet.clear();
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (elapsed < tickRate) {
            std::this_thread::sleep_for(tickRate - elapsed);
            _tick++;
        }
    }
}

void ServerGame::manaRegenScript(int entityId, World &world)
{
    static std::map<int, float> regenTimers;

    const auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity) {
        regenTimers.erase(entityId);
        return;
    }
    auto data = entity->getComponent<Data>();
    if (!data)
        return;
    int currentMana = std::stoi(data->getData("mana"));
    int maxMana = std::stoi(data->getData("max_mana"));
    if (currentMana >= maxMana)
        return;
    float dt = world.getDeltaTime();
    regenTimers[entityId] += dt;
    if (regenTimers[entityId] >= 2.0f) {
        regenTimers[entityId] = 0.0f;
        currentMana += 1;
        if (currentMana > maxMana)
            currentMana = maxMana;
        data->setData("mana", std::to_string(currentMana));
        _packet.action(entityId, MANA, currentMana);
    }
}

/**
 * @brief Creates the player entity.
 *
 * @param x The x position of player.
 * @param y The y position of player.
 * This function initializes the player entity with necessary components.
 */
void ServerGame::createPlayer(const float x, const float y)
{
    const auto player = _world.createEntity();
    player->addComponent<HP>(100);
    player->addComponent<Position>(x, y);
    player->addComponent<BoxCollider>(10.f, 10.f);
    player->addComponent<Tag>("player");
    player->addComponent<Damage>(10);
    std::map<std::string, std::string> dataMap = {
        {"mana", "100"},
        {"max_mana", "100"}
    };
    player->addComponent<Data>(dataMap);
    player->addComponent<Script>(
       [this](const int entityId, World& world)
       {
           this->manaRegenScript(entityId, world);
       }
   );
    _packet.Spawn(player->getId(), Player, x, y);
    for (const auto& entity : _world.getAllEntitiesWithComponent<Tag>()) {
        const auto pos = entity->getComponent<Position>();
        const auto tag = entity->getComponent<Tag>();
        entitiesType type = None;
        if (entity->getId() == player->getId())
            continue;
        if (tag->getTag() == "player")
            type = Player;
        else if (tag->getTag() == "enemy")
            type = Enemy;
        else if (tag->getTag() == "bullet")
            type = Bullet;
        _packet.Spawn(entity->getId(), type, pos->getX(), pos->getY());
    }
}

/**
 * @brief define the movement of an enemy.
 *
 * @param entityId the ID if the entity.
 * @param world the world where all entity are contains.
 * @param network network interface
 */
void ServerGame::EnemyMovement(const uint32_t entityId, World &world)
{
    const auto entity = GameHelper::getEntityById(world, entityId);

    if (!entity)
        return;
    auto hpComp = entity->getComponent<HP>();
    if (!hpComp || !hpComp->isAlive())
        return;
    auto pos = entity->getComponent<Position>();
    pos->setX(pos->getX() - 1 * world.getDeltaTime());

    _packet.updatePosition(entityId, pos->getX(), pos->getY());
}

void ServerGame::EnemySinusMovement(uint32_t entityId, World& world)
{
    static std::map<int, float> timers;
    static std::map<int, float> startYPos;

    const auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity) {
        return;
    }
    auto hpComp = entity->getComponent<HP>();
    if (!hpComp)
        return;
    if (!hpComp->isAlive())
        return;
    auto pos = entity->getComponent<Position>();
    if (startYPos.find(entityId) == startYPos.end())
        startYPos[entityId] = pos->getY();

    float dt = world.getDeltaTime();
    float speedX = 2.0f;
    float sinusSpeed = 0.03f;
    float amplitude = 200.0f;
    pos->setX(pos->getX() - speedX * dt);
    timers[entityId] += dt * sinusSpeed;
    pos->setY(startYPos[entityId] + std::sin(timers[entityId]) * amplitude);
    _packet.updatePosition(entityId, pos->getX(), pos->getY());
}

void ServerGame::ShootingAction(int entityId, World& world)
{
    static std::map<int, float> timers;

    const auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity)
        return;

    auto hpComp = entity->getComponent<HP>();
    if (!hpComp || !hpComp->isAlive())
        return;
    auto pos = entity->getComponent<Position>();
    float dt = world.getDeltaTime();
    timers[entityId] += dt;
    if (timers[entityId] >= 60.0f)
    {
        timers[entityId] = 0.0f;
        createEnemyBullet(pos->getX() + 30, pos->getY() + 30);
    }
}

/**
 * @brief Creates a Ennemy entity.
 *
 * @param x The x position of the enemy.
 * @param y The y position of the enemy.
 * This function initializes the player entity with necessary components.
 */
void ServerGame::createEnemy(const float x, const float y)
{
    const auto enemy = _world.createEntity();
    enemy->addComponent<HP>(100);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
    enemy->addComponent<Velocity>(-3.0f, 0.0f);
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<Script>(
        [this](const int entityId, World& world)
        {
            this->EnemyMovement(entityId, world);
        }
    );
    _packet.Spawn(enemy->getId(), Enemy, x, y);
}

void ServerGame::createFast(const float x, const float y)
{
    const auto enemy = _world.createEntity();
    enemy->addComponent<HP>(50);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<Velocity>(-5.0f, 0.0f);
    enemy->addComponent<Script>(
        [this](const int entityId, World& world)
        {
            this->EnemyMovement(entityId, world);
        }
    );
    _packet.Spawn(enemy->getId(), Fast, x, y);
}

void ServerGame::createTank(const float x, const float y)
{
    const auto enemy = _world.createEntity();
    enemy->addComponent<HP>(150);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
    enemy->addComponent<Velocity>(-1.0f, 0.0f);
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<Script>(
        [this](const int entityId, World& world)
        {
            this->EnemyMovement(entityId, world);
        }
    );
    _packet.Spawn(enemy->getId(), Tank, x, y);
}

void ServerGame::createSinusEnemy(const float x, const float y)
{
    const auto enemy = _world.createEntity();
    enemy->addComponent<HP>(150);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<Script>(
        [this](const int entityId, World& world)
        {
            this->EnemySinusMovement(entityId, world);
        }
    );
    _packet.Spawn(enemy->getId(), EnemySinus, x, y);
}

void ServerGame::createShootingEnemy(const float x, const float y)
{
    const auto enemy = _world.createEntity();
    enemy->addComponent<HP>(150);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<BoxCollider>(66.0f, 52.0f);
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<Script>(
        [this](const int entityId, World& world)
        {
            this->EnemyMovement(entityId, world);
            this->ShootingAction(entityId, world);
        }
    );
    _packet.Spawn(enemy->getId(), ShootingEnemy, x, y);
}

void ServerGame::createSinusShootingEnemy(const float x, const float y)
{
    const auto enemy = _world.createEntity();
    enemy->addComponent<HP>(150);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<Script>(
        [this](const int entityId, World& world)
        {
            this->EnemySinusMovement(entityId, world);
            this->ShootingAction(entityId, world);
        }
    );
    _packet.Spawn(enemy->getId(), ShootingEnemy, x, y);
}

void ServerGame::createHealPowerUp(const float x, const float y)
{
    const auto enemy = _world.createEntity();
    enemy->addComponent<HP>(10);
    enemy->addComponent<Damage>(0);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<BoxCollider>(66.0f, 60.0f);
    enemy->addComponent<Tag>("heal");
    enemy->addComponent<Script>(
        [this](const int entityId, World& world)
        {
            this->EnemyMovement(entityId, world);
        }
    );
    _packet.Spawn(enemy->getId(), HealPU, x, y);
}

/**
 * @brief Create a wave of enemies
 */
void ServerGame::createWave()
{
    std::cout << "Spawning enemy wave!" << std::endl;
    for (int i = 0; i < 10; i++)
        createEnemy(1920 + static_cast<float>(i) * 100, 200 + static_cast<float>(i % 3) * 250);
}

/**
 * @brief define the movement of a bullet.
 *
 * @param entityId the ID if the entity.
 * @param world the world where all entity are contains.
 */
void ServerGame::BulletMovement(const uint32_t entityId, World &world)
{
    const auto entity = GameHelper::getEntityById(world, entityId);
    const auto vel = entity->getComponent<Velocity>();
    const auto pos = entity->getComponent<Position>();

    if (vel) {
        pos->setX(pos->getX() + vel->getVelocityX() * world.getDeltaTime());
        pos->setY(pos->getY() + vel->getVelocityY() * world.getDeltaTime());
    }
    if (pos->getX() > 2800 || pos->getX() < -100) {
        world.killEntity(entityId);
        _packet.dead(entityId);
    } else {
        pos->setX(pos->getX() + 10 * world.getDeltaTime());
        _packet.updatePosition(entityId, pos->getX(), pos->getY());
    }
}

/**
 * @brief Create a bullet.
 *
 * @param x The x position of the bullet on apparition.
 * @param y The y position of the bullet on apparition.
 */
void ServerGame::createBullet(const float x, const float y)
{
    const auto bullet = _world.createEntity();

    bullet->addComponent<Position>(x + 60.f, y + 15.f);
    bullet->addComponent<BoxCollider>(64.0f, 30.0f);
    bullet->addComponent<Velocity>(10.f, 0.f);
    bullet->addComponent<Tag>("player_bullet");
    bullet->addComponent<HP>(10);
    bullet->addComponent<Damage>(50);
    bullet->addComponent<Script>(
        [this](const uint32_t entityId, World& world)
        {
            this->BulletMovement(entityId, world);
        }
    );
    _packet.Spawn(bullet->getId(), Bullet, x + 60.f, y + 15.f);
}

void ServerGame::createEnemyBullet(const float x, const float y)
{
    const auto bullet = _world.createEntity();

    bullet->addComponent<Position>(x - 60.f, y + 15.f);
    bullet->addComponent<BoxCollider>(64.0f, 30.0f);
    bullet->addComponent<Velocity>(-10.f, 0.f);
    bullet->addComponent<Tag>("enemy_bullet");
    bullet->addComponent<Damage>(10);
    bullet->addComponent<HP>(10);
    bullet->addComponent<Script>(
        [this](const int entityId, World& world)
        {
            this->BulletMovement(entityId, world);
        }
    );
    _packet.Spawn(bullet->getId(), EnemyBullet, x + 60.f, y + 15.f);
}

void ServerGame::createEnemyBackwardBullet(const float x, const float y)
{
    const auto bullet = _world.createEntity();

    bullet->addComponent<Position>(x - 60.f, y + 15.f);
    bullet->addComponent<BoxCollider>(64.0f, 30.0f);
    bullet->addComponent<Velocity>(5.f, 0.f);
    bullet->addComponent<Tag>("enemy_bullet");
    bullet->addComponent<Damage>(10);
    bullet->addComponent<HP>(10);
    bullet->addComponent<Script>(
        [this](const int entityId, World& world)
        {
            this->BulletMovement(entityId, world);
        }
    );
    _packet.Spawn(bullet->getId(), BackwardEnemyBullet, x + 60.f, y + 15.f);
}

/**
 * @brief Create a new player when a client connect.
 */
void ServerGame::handleNewPlayer()
{
    if (_playerCount >= MAX_PLAYER) {
        std::cout << "Maximum number of players reached (" << MAX_PLAYER << ")" << std::endl;
        return;
    }

    createPlayer(200, 300 + (_playerCount) * 100);
    _playerCount++;

    std::cout << "Player " << _playerCount << " connected" << std::endl;
}

/**
 * @brief Handle player ready status
 *
 * @param playerId The id of the player who is ready
 */
void ServerGame::handlePlayerReady(const uint32_t playerId)
{
    _readyCount++;
    std::cout << "Player " << playerId << " is ready. Ready count: " << _readyCount << "/" << _playerCount << std::endl;

    if (_readyCount == NB_PLAYER_TO_START && !_gameStarted && _playerCount >= NB_PLAYER_TO_START) {
        _gameStarted = true;
        _waveTimer.restart();
        Packet startPacket;
        startPacket.setId(0).setAck(0).setPacketNbr(1).setTotalPacketNbr(1);
        startPacket.startGame();
        _network.sendPacket(startPacket);
        _levelLoader.loadFromFile(5, this);   // Need to change that later to have a level management
        std::cout << "Game started!" << std::endl;
        startLevel(4);   // Need to change that later to have a level management
    }
}

/**
 * @brief check if the new position send by the client is valid and change it in server side.
 *
 * @param id The id of the player who is moving.
 * @param x The new x position of the player.
 * @param y The new y position of the player.
 */
void ServerGame::serverUpdatePosition(const uint32_t id, const float x, const float y)
{
    const auto entity = GameHelper::getEntityById(_world, id);

    if (entity == nullptr) {
        std::cerr << "[Warning] Ignore position update for unknown entity ID: " << id << std::endl;
        return;
    }

    const auto pos = entity->getComponent<Position>();

    const auto distanceX = pos->getX() - x;
    const auto distanceY = pos->getY() - y;

    // if is not good for now just set the position
    //if (distanceX * distanceX + distanceY * distanceY <= 20.f) {
    //    pos->setX(x);
    //    pos->setY(y);
    //}
    pos->setX(x);
    pos->setY(y);
    _packet.updatePosition(id, x, y);
}

/**
 * @brief Create a bullet at the place of the player who is shooting.
 *
 * @param id The id of the player who is shooting.
 */
void ServerGame::handleShoot(const uint32_t id)
{
    const auto entity = GameHelper::getEntityById(_world, id);
    if (!entity) {
        return;
    }
    const auto pos = entity->getComponent<Position>();
    const auto data = entity->getComponent<Data>();
    if (!pos || !data)
        return;
    int currentMana = std::stoi(data->getData("mana"));
    const int manaCost = 5;
    if (currentMana < manaCost)
        return;
    currentMana -= manaCost;
    data->setData("mana", std::to_string(currentMana));
    _packet.action(id, MANA, currentMana);
    createBullet(pos->getX(), pos->getY());
}

void ServerGame::handleHeal(const uint32_t id)
{
    auto player = GameHelper::getEntityById(_world, id);
    if (!player)
        return;
    auto hp = player->getComponent<HP>();
    if (!hp)
        return;
    unsigned int currentHp = hp->getHP();
    unsigned int maxHp = hp->getMaxHP();
    unsigned int newHp = std::min(currentHp + 20, maxHp);
    hp->setHP(newHp);
    _packet.action(id, HEAL, newHp);
}

void ServerGame::checkDeaths()
{
    auto entities = _world.getAllEntitiesWithComponent<HP>();

    for (const auto& entity : entities) {
        if (!entity)
            continue;
        auto hp = entity->getComponent<HP>();
        if (!hp || hp->getHP() > 0)
            continue;
        if (hp->isAlive()) {
            if (_packet.getPacket().getDataSize() != 12) {
                _network.sendPacket(_packet);
                _packet.clear();
            }
            hp->setAlive(false);
            _packet.dead(entity->getId());
            _world.killEntity(entity->getId());
            _packet.setAck(getAckId());
            _ackPackets.emplace_back(_packet, _tick);
            for (auto tmp : _users)
                tmp._ackList.emplace_back(_tick);
            _network.sendPacket(_packet);
            _packet.setAck(0);
            _packet.clear();
        }
    }
}

void ServerGame::createWarningPortal(float x, float y, float duration)
{
    auto portal = _world.createEntity();
    portal->addComponent<Position>(x, y);
    portal->addComponent<Tag>("warning_portal");
    portal->addComponent<Data>(std::map<std::string, std::string>{
        {"type", "warning"},
        {"lifetime", "0"},
        {"duration", std::to_string(duration)}
    });
    portal->addComponent<Script>(
        [this](int entityId, World& world) {
            auto entity = GameHelper::getEntityById(world, entityId);
            if (!entity) return;
            auto data = entity->getComponent<Data>();
            float lifetime = std::stof(data->getData("lifetime"));
            float duration = std::stof(data->getData("duration"));
            lifetime += world.getDeltaTime();
            data->setData("lifetime", std::to_string(lifetime));
            if (lifetime >= duration) {
                world.killEntity(entityId);
                _packet.dead(entityId);
            }
        }
    );
    _packet.Spawn(portal->getId(), Portal, x, y);
}

void ServerGame::portalBossBackwardPortalScript(int entityId, World& world)
{
    static std::map<int, int> phase;
    static std::map<int, float> phaseTimer;

    const auto boss = GameHelper::getEntityById(world, entityId);
    if (!boss)
        return;
    float dt = world.getDeltaTime();
    phaseTimer[entityId] += dt;
    if (phase[entityId] == 0 && phaseTimer[entityId] >= 90.0f) {
        float leftX = 100.0f;
        for (int i = 0; i < 5; i++) {
            float yPos = 200.0f + (i * 150.0f);
            createWarningPortal(leftX, yPos, 60.0f);
        }
        phase[entityId] = 1;
        phaseTimer[entityId] = 0.0f;
    }
    else if (phase[entityId] == 1 && phaseTimer[entityId] >= 30.0f) {
        phase[entityId] = 2;
        phaseTimer[entityId] = 0.0f;
    }
    else if (phase[entityId] == 2) {
        float leftX = 100.0f;
        for (int i = 0; i < 5; i++) {
            float yPos = 200.0f + (i * 150.0f);
            createEnemyBackwardBullet(leftX, yPos);
        }
        phase[entityId] = 3;
        phaseTimer[entityId] = 0.0f;
    }
    else if (phase[entityId] == 3 && phaseTimer[entityId] >= 60.0f) { // 2 secondes
        phase[entityId] = 0;
        phaseTimer[entityId] = 0.0f;
    }
}



void ServerGame::portalBossBarrageScript(int entityId, World &world)
{
    static std::map<int, float> shootTimers;
    static std::map<int, float> shootTimers2;
    const auto boss = GameHelper::getEntityById(world, entityId);

    if (!boss)
        return;
    auto hpComp = boss->getComponent<HP>();
    if (!hpComp || !hpComp->isAlive())
        return;
    auto pos = boss->getComponent<Position>();
    float dt = world.getDeltaTime();
    shootTimers[entityId] += dt;
    shootTimers2[entityId] += dt;
    if (shootTimers[entityId] >= 60.0f) {
        shootTimers[entityId] = 0.0f;
        float centerOffset = 500.0f;
        for (int i = 0; i < 5; i++) {
            float offsetY = (i - 2) * 50.0f;
            createEnemyBullet(pos->getX() - 50, pos->getY() + centerOffset + offsetY);
        }
    }
    if (shootTimers2[entityId] >= 90.0f) {
        shootTimers2[entityId] = 0.0f;
        float centerOffset = 300.0f;
        float centerOffset2 = 700.0f;
        for (int i = 0; i < 5; i++) {
            float offsetY = (i - 2) * 50.0f;
            createEnemyBullet(pos->getX() - 50, pos->getY() + centerOffset + offsetY);
            createEnemyBullet(pos->getX() - 50, pos->getY() + centerOffset2 + offsetY);
        }
    }
}

void ServerGame::portalBossSpawnTankScript(int entityId, World& world)
{
    static std::map<int, float> spawnTimer;
    static std::map<int, float> spawnTimer2;

    const auto boss = GameHelper::getEntityById(world, entityId);
    if (!boss)
        return;
    auto pos = boss->getComponent<Position>();
    float dt = world.getDeltaTime();
    spawnTimer[entityId] += dt;
    spawnTimer2[entityId] += dt;
    if (spawnTimer[entityId] >= 300.0f) {
        spawnTimer[entityId] = 0.0f;
        float offsetY =  800.0f;
        createTank(pos->getX(), pos->getY() + 60.0f);
        createTank(pos->getX(), pos->getY() + 60.0f + offsetY);


    }
}


void ServerGame::createPortalBoss(const float x, const float y)
{
    const auto enemy = _world.createEntity();
    enemy->addComponent<HP>(5000);
    enemy->addComponent<Damage>(10);
    enemy->addComponent<Position>(x, y);
    enemy->addComponent<BoxCollider>(50.0f, 5000.0f);
    enemy->addComponent<Tag>("enemy");
    enemy->addComponent<Script>(
        [this](const int entityId, World& world)
        {
            this->portalBossBarrageScript(entityId, world);
            this->portalBossBackwardPortalScript(entityId, world);
          //  this->portalBossSpawnTankScript(entityId, world);
        }
    );
    _packet.Spawn(enemy->getId(), PortalBoss, x, y);
}

/**
 * @brief Receive action with id and data and call corresponding function
 *
 * @param id
 * @param action
 * @param data
 */
void ServerGame::handleAction(const uint32_t id, const uint8_t action, const uint32_t data)
{
    switch (action)
    {
        case FIRE : {
            handleShoot(id);
            break;
        }
        case HEAL : {
            handleHeal(id);
            break;
        }
        case SHIELD : {
            break;
        }
        case BEAM : {
            break;
        }
        default:
            ;
    }
}


void ServerGame::sendGameEnd(uint8_t status)
{
    Packet packet;
    packet.endGame(status);
    _network.sendPacket(packet);
}

void ServerGame::checkGameEnd()
{
    if (!_gameStarted)
        return;
    auto players = _world.getAllEntitiesWithComponent<Tag>();
    int alivePlayers = 0;
    for (const auto& entity : players) {
        auto tag = entity->getComponent<Tag>();
        if (tag && tag->getTag() == "player") {
            auto hp = entity->getComponent<HP>();
            if (hp && hp->isAlive() && hp->getHP() > 0) {
                alivePlayers++;
            }
        }
    }
    if (alivePlayers == 0 && _playerCount > 0) {
        static bool gameOverSent = false;
        if (!gameOverSent) {
            std::cout << "GAME OVER - All players dead!" << std::endl;
            sendGameEnd(0);
            gameOverSent = true;
        }
        return;
    }
    auto enemies = _world.getAllEntitiesWithComponent<Tag>();
    bool enemyAlive = false;
    for (const auto& entity : enemies) {
        auto tag = entity->getComponent<Tag>();
        if (tag && tag->getTag() == "enemy") {
            auto hp = entity->getComponent<HP>();
            if (hp && hp->isAlive() && hp->getHP() > 0) {
                enemyAlive = true;
                break;
            }
        }
    }
    static bool victorySent = false;
    if (!enemyAlive && !victorySent && alivePlayers > 0) {
        victorySent = true;
        std::cout << "VICTORY - All enemies defeated!" << std::endl;
        sendGameEnd(1);
    }
}
