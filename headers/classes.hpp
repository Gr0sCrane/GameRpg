#pragma once
#include <array>
#include <vector>
#include <memory>
#include <string>
#include <functional>

/**
 * @enum EntityType
 * @brief Enum class that represent the Type of the Entity: Player,Mob,Item
 */
enum class EntityType {
    PLAYER,
    MOB,
    ITEM,
    VOID
};

/**
 * @struct Position
 * @brief Represent a position on the board.
 * @param x X coord
 * @param y Y coord
 */
struct Position {
    int x;
    int y;

    Position(int x = 0,int y = 0) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

};
namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& pos) const {
            return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
        }
    };
}

class Entity {
    private:
    EntityType type;
    double hp;
    double attack;
    Position Pos;
    public:
    Entity(EntityType t, double hp, double attack, Position pos);
    virtual ~Entity();
    
    bool isAlive() const;
    virtual std::string getClassName() const;
    
    void setPosition(Position pos);
    Position getPosition();
    
    EntityType getType() const;
};

class Item : public Entity {
    private:
    std::string name;
    public:
    Item(const std::string& itemName,Position pos);
    virtual ~Item() override;
    
    std::string getName() const;
    void setName(const std::string& newName);
};

class Inventory {
private:
    std::vector<std::unique_ptr<Item>> items;
    static constexpr size_t MAX_INV_SIZE = 5;
public:
    Inventory();
    bool addItem(std::unique_ptr<Item> item);
    void removeItem(const std::string& name);
    void removeFirstItem();
    const std::vector<std::unique_ptr<Item>>& getItems() const;
    size_t getSize() const;
    size_t getMaxSize() const;
    bool isEmpty();
};

class Stats {
public:
    int hp;
    double attack;
    double defense;
    int xp;
    int level;
    int maxHp = 30;

    Stats(int hp,double attack, double defense = 2,int xp = 0,int level = 1) :
    hp(hp), attack(attack), defense(defense), xp(xp), level(level) {}

    void gainXp(int amount);
    void checkLvlUp();
    int getXpToNxtLvl();

};

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

class Heal : public Item {
private:
    double healAmount;
public:
    Heal(const std::string& itemName, double healamount,Position pos);
    double getHealAmount() const;
    void setHealAmount(double newAmount);
    virtual std::string getClassName() const override;
};

class Weapon : public Item {
private:
    double attackPoints;
public:
    Weapon(const std::string& itemName, double attack,Position pos);
    double getAttackPoints() const;
    void setAttackPoints(double newAttack);
};

class Sword : public Weapon {
public:
    Sword(const std::string& itemName, double attack, Position pos);
    virtual std::string getClassName() const override;
};

class Bow : public Weapon {
private:
    double range;
public:
    Bow(const std::string& itemName, double attack, double range, Position pos);
    double getRange() const;
    void setRange(double newRange);
    virtual std::string getClassName() const override;
};
