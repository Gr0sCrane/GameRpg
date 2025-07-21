#include <iostream>
#include "player.hpp"
#include "mob.hpp"

Player::Player(Position pos)
    : Entity(EntityType::PLAYER,20,5,pos),
    stats(20,5.0,3.0),
    inventory() {}

Inventory& Player::getInventory() {
    return inventory;
}

Stats& Player::getStats() {
    return stats;
}

const Stats& Player::getStats() const {
    return stats;
}

void Player::attack(std::shared_ptr<Mob> mob) {

    double attack = getStats().attack;
    double defense = mob->getStats().defense;
    double damage = attack * (100.0 / (100.0 + defense));

    double mobHp = mob->getStats().hp;
    mobHp -= damage;
    if (mobHp < 0) mobHp = 0;

    mob->getStats().hp = mobHp;
}

bool Player::isPlayerProtecting() const {
    return isProtecting;
}

void Player::setPlayerProtecting(bool e){
    isProtecting = e;
}

double Player::protect(double attackAmount){
    if (!isPlayerProtecting()){
        return 0;
    }
    double damageReductionFactor = 0.5; // 50% of shield protection
    double newAttackAmount = attackAmount * damageReductionFactor;

    return newAttackAmount;
}