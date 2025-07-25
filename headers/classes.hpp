#pragma once
#include <array>
#include <vector>
#include <memory>
#include <string>
#include "entity.hpp"

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
