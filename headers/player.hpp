#pragma once
#include <iostream>
#include "classes.hpp"

class Mob;

class Player : public Entity {
private:
    Stats stats;
    Inventory inventory;
    bool isProtecting = false;
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