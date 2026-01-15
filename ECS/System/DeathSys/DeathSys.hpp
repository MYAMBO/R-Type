/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** DeathSys
*/

#ifndef R_TYPE_DEATHSYS_H
    #define R_TYPE_DEATHSYS_H

#include "System.hpp"
#include "World.hpp"
#include "HP.hpp"
#include <map>
#include <vector>
#include "IGameNetwork.hpp"

class DeathSys : public System {
private:
    std::map<uint64_t, float> _deathTimers;
    std::vector<uint64_t> _entitiesToKill;
    IGameNetwork& _network;

public:
    // DeathSys() = default;
    DeathSys(IGameNetwork& network) : _network(network) {}
    ~DeathSys() override = default;

    void update(const float& dt, World &w) override;
};

#endif //R_TYPE_DEATHSYS_H