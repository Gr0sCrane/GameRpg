#include <iostream>
#include "player.hpp"
#include "mob.hpp"

/**
 * @brief Constructor of the player class.
 * @param pos the position of the player.
 */
Player::Player(Position pos)
    : Entity(EntityType::PLAYER,20,5,pos),
    stats(20,5.0,3.0),
    inventory() {}

/**
 * @brief Getter for the player inventory.
 * @return the inventory of the player.
 */
Inventory& Player::getInventory() {
    return inventory;
}

/**
 * @brief Getter for the player's stats.
 * @return the stats of the player.
 */
Stats& Player::getStats() {
    return stats;
}

/**
 * @brief Attack the targeted enemy using the attack point.
 * 
 * the damage is calculated with the attack multiplied by 100 and divided by 100 + enemy's defense.
 * the enemy lose the amount of hp related to the attack point of the player.
 * @param mob the enemy targeted.
 */
void Player::attack(std::shared_ptr<Mob> mob) {

    double attack = getStats().attack;
    double defense = mob->getStats().defense;
    double damage = attack * (100.0 / (100.0 + defense));

    double mobHp = mob->getStats().hp;
    mobHp -= damage;
    if (mobHp < 0) mobHp = 0;

    mob->getStats().hp = mobHp;
}

/**
 * @brief Boolean function that indicate if the player is protecting or not.
 * @return true: yes, false: no.
 */
bool Player::isPlayerProtecting() const {
    return isProtecting;
}

/**
 * @brief Setter for the player protecting status.
 * @see isPlayerProtecting()
 * @param e the boolean value to give. (true / false)
 */
void Player::setPlayerProtecting(bool e){
    isProtecting = e;
}

/**
 * @brief Function that reduce by 50% the amount of damage using the defense stats.
 * @param attackAmount the amount of damage the player receive.
 * @return the attack amount multiplied by the damage reduction factor (50%).
 */
double Player::protect(double attackAmount){
    if (!isPlayerProtecting()){
        return 0;
    }
    double damageReductionFactor = 0.5; // 50% of shield protection
    double newAttackAmount = attackAmount * damageReductionFactor;

    return newAttackAmount;
}