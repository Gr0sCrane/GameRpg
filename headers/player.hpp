/*-Header file of src/player.cpp-*/
#pragma once
#include <iostream>
#include "classes.hpp"

class Mob;

/**
 * @class Player
 * @brief Represent a player
 * 
 */
class Player : public Entity {
private:
    Stats stats;
    Inventory inventory;
    bool isProtecting = false; // indicate if the player is protecting or not. At default false.
public:
    Player(Position pos);
    Inventory& getInventory();
    Stats& getStats();
    const Stats& getStats() const;
    void attack(std::shared_ptr<Mob> mob);
    double protect(double attackAmount);
    bool isPlayerProtecting() const;
    void setPlayerProtecting(bool e);
};