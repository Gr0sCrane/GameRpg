#include <iostream>
#include "classes.hpp"
#include "player.hpp"

class Mob : public Entity {
private:
    std::string mobname;
    Stats stats;
    Inventory inventory;
public:
    Mob(const std::string& name,Stats stats,Position pos);
    std::string getMobName() const;
    void setMobName(const std::string& newName);
    virtual std::string getClassName() const override;
    Stats& getStats();
    const Stats& getStats() const;
    void attackPlayer(std::shared_ptr<Player> player);
};