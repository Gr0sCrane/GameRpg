#include <iostream>
#include "mob.hpp"

Mob::Mob(const std::string& name,Stats Stats,Position pos) : Entity(EntityType::MOB,25.0,3.0,pos), mobname(name),
    stats(25.0,3.0,0),
    inventory() {}
std::string Mob::getClassName() const { return "Mob"; }
std::string Mob::getMobName() const { return mobname; }
void Mob::setMobName(const std::string& newName) { mobname = newName; }

Stats& Mob::getStats() {
    return stats;
}

const Stats& Mob::getStats() const {
    return stats;
}

void Mob::attackPlayer(std::shared_ptr<Player> player) {
    double attackAmount = getStats().attack;
    double finalDamage;

    if (player->isPlayerProtecting()) {
        finalDamage = player->protect(attackAmount);
    } else {
        double defense = player->getStats().defense;
        finalDamage = attackAmount * (100.0 / (100.0 + defense));
    }

    double playerHp = player->getStats().hp;
    playerHp -= finalDamage;
    if (playerHp < 0) playerHp = 0;

    player->getStats().hp = playerHp;
}