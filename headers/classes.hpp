/*-Header file of src/classes.cpp-*/
#pragma once
#include <array>
#include <vector>
#include <memory>
#include <string>
#include "entity.hpp"

/**
 * @class Item
 * @brief represent an item.
 */
class Item : public Entity {
private:
    std::string name;
public:
    Item(const std::string& itemName,Position pos);
    virtual ~Item() = default;

    virtual std::unique_ptr<Item> clone() const = 0;
    std::string getName() const;
    void setName(const std::string& newName);
};

/**
 * @class Inventory
 * @brief represent the inventory
 */
class Inventory {
private:
    std::vector<std::shared_ptr<Item>> items;
    static constexpr size_t MAX_INV_SIZE = 5; // maximum size of the inventory.
public:
    Inventory();
    bool addItem(std::shared_ptr<Item> item);
    void removeItem(const std::string& name);
    void removeFirstItem();
    const std::vector<std::shared_ptr<Item>>& getItems() const;
    size_t getSize() const;
    size_t getMaxSize() const;
    bool isEmpty();
};

/**
 * @class Stats
 * @brief represent the statistics of an entity.
 * 
 */
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

/**
 * @class Heal
 * @brief represent a heal item
 * @see Item
 */
class Heal : public Item {
private:
    double healAmount; //the amount of hp the heal item can give. <Double>
public:
    Heal(const std::string& itemName, double healamount,Position pos);
    double getHealAmount() const;
    void setHealAmount(double newAmount);
    virtual std::string getClassName() const override;

    virtual std::unique_ptr<Item> clone() const override {
        return std::make_unique<Heal>(*this);
    }
};

/**
 * @class Weapon
 * @brief represent a weapon item.
 * 
 * @see Item
 */
class Weapon : public Item {
private:
    double attackPoints; //the amount of attack points the item can do.
public:
    Weapon(const std::string& itemName, double attack,Position pos);
    double getAttackPoints() const;
    void setAttackPoints(double newAttack);
};

/**
 * @class Sword
 * @brief represent a sword item.
 * @see Item
 */
class Sword : public Weapon {
public:
    Sword(const std::string& itemName, double attack, Position pos);
    virtual std::string getClassName() const override;

    virtual std::unique_ptr<Item> clone() const override {
        return std::make_unique<Sword>(*this);
    }
};

/**
 * @class Bow
 * @brief represent a bow item.
 * @see Item
 */
class Bow : public Weapon {
private:
    double range; // the range of the bow.
public:
    Bow(const std::string& itemName, double attack, double range, Position pos);
    double getRange() const;
    void setRange(double newRange);
    virtual std::string getClassName() const override;

    virtual std::unique_ptr<Item> clone() const override {
        return std::make_unique<Bow>(*this);
    }
};
