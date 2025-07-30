#include "classes.hpp"
#include <iostream>

//|================================|Class Item|======================================|

/**
 * @brief Constructor of the Item class.
 * @param itemName the name of the item
 * @param pos The position on the board of the item.
 */
Item::Item(const std::string& itemName,Position pos)
    : Entity(EntityType::ITEM, 0, 0, pos), name(itemName) {}

/**
 * @brief Getter for the Item's name.
 * @return The item's name.
 */
std::string Item::getName() const { return name; }

/**
 * @brief Setter for the Item's name.
 * @param newName the new name of the item.
 */
void Item::setName(const std::string& newName) { name = newName; }

//================================|Class Inventory|===================================|

/**
 * @brief Constructor of the Inventory class.
 */
Inventory::Inventory(){};

/**
 * @brief Add an item in the inventory.
 * 
 * If the item does'nt exist the function return an error.
 * 
 * @param item the item added to the inventory.
 * @return A boolean that indicate if the item has been added or not.
 */
bool Inventory::addItem(std::shared_ptr<Item> item) {
    if (!item) {
        std::cerr << "Item is null" << std::endl;
        return false;
    }
    if (items.size() >= MAX_INV_SIZE) return false;
    
    items.push_back(item);
    return true;
}

/**
 * @brief Remove the item from the inventory.
 * @param itemName the item's name that are removed.
 */
void Inventory::removeItem(const std::string& itemName) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getName() == itemName) {
            items.erase(it);
            return;
        }
    }
}

/**
 * @brief Remove the first item in the inventory.
 */
void Inventory::removeFirstItem(){
    if (!items.empty()){
        auto i = items.begin();
        items.erase(i);
    }
}

/**
 * @brief Getter for the inventory.
 * @return all the items stored in the inventory.
 */
const std::vector<std::shared_ptr<Item>>& Inventory::getItems() const {
    return items;
}

/**
 * @brief Getter for the inventory's size.
 * @return The size of the inventory.
 */
size_t Inventory::getSize() const {
    return items.size();
}

/**
 * @brief Return the max size of the inventory.
 * @return The max size
 */
size_t Inventory::getMaxSize() const {
    return MAX_INV_SIZE;
}

/**
 * @brief Indicate if the inventory is rempty or not.
 * @return True if yes, false if not.
 */
bool Inventory::isEmpty() {
    return items.empty();
}

//============================|Class Stats|=========================================|

/**
 * @brief Checks if the player has level up with the needed amount of xp.
 * 
 * If yes then all the statistics of the player get incremented with specifics values.
 */
void Stats::checkLvlUp(){
    int threshold = level * 10;
    while (xp >= threshold) {
        xp -= threshold;
        level++;
        maxHp += 5;
        hp = maxHp;
        attack += 2;
        defense += 0.5;
        std::cout << "Level Up !" << std::endl;

        threshold = level * (2 * level);
    }
}

/**
 * @brief Add the amount of xp given in parameter to the entity's xp stat.
 * @see checkLvlUp().
 * @param amount the amount given to the entity's xp stat.
 */
void Stats::gainXp(int amount){
    xp += amount;
    checkLvlUp();
}

/**
 * @brief Indicate how much xp needed to reach the next level.
 * @return the amount needed for next level.
 */
int Stats::getXpToNxtLvl(){
    int threshold = level * 10;
    return threshold - xp;
}


//|================================|Class Heal|======================================|

/**
 * @brief Constructor of the Heal item entity.
 * @param itemName the name of the Heal item.
 * @param amount the amount of health points the item gives.
 * @param pos the position of the Heal item on the board.
 */
Heal::Heal(const std::string& itemName, double amount, Position pos)
    : Item(itemName,pos), healAmount(amount) {
    if (amount < 0) {
        std::cerr << "Heal amount cannot be negative. Setting to 0." << std::endl;
        healAmount = 0;
    }
}

/**
 * @brief Getter for the amount of health point the Heal item gives.
 * @return the amount of hp the Heal item gives.
 */
double Heal::getHealAmount() const { return healAmount; }

/**
 * @brief Setter for the amount of hp the Heal item gives.
 * @param newAmount the new amount of hp the Heal item gives.
 */
void Heal::setHealAmount(double newAmount) {
    if (newAmount < 0) {
        std::cerr << "Heal amount cannot be negative. Setting to 0." << std::endl;
        newAmount = 0;
    }
    healAmount = newAmount;
}

/**
 * @brief Getter for the class name.
 * @return the name of the class.
 */
std::string Heal::getClassName() const { return "Heal"; }

//|================================|Class Weapon|======================================|

/**
 * @brief Constructor of the Weapon class.
 * @param itemName the name of the weapon.
 * @param attack the attack points of the Weapon.
 * @param pos the position on the board of the Weapon.
 */
Weapon::Weapon(const std::string& itemName, double attack, Position pos)
    : Item(itemName,pos), attackPoints(attack) {
    if (attack < 0) {
        std::cerr << "Attack points cannot be negative. Setting to 0." << std::endl;
        attackPoints = 0;
    }
}

/**
 * @brief Getter for the attack points stats for a Weapon item.
 * @return the attack points of the Weapon.
 */
double Weapon::getAttackPoints() const { return attackPoints; }

/**
 * @brief Setter for the attack points stats for a Weapon item.
 * @param newAttack the new attack points of the Weapon.
 */
void Weapon::setAttackPoints(double newAttack) {
    if (newAttack < 0) {
        std::cerr << "Attack points cannot be negative. Setting to 0." << std::endl;
        newAttack = 0;
    }
    attackPoints = newAttack;
}

//|================================|Class Sword|======================================|

/**
 * @brief Constructor of the Sword class.
 * @param itemName the sword's name.
 * @param attack the attack points of the sword.
 * @param pos the position of the sword on the board.
 */
Sword::Sword(const std::string& itemName, double attack, Position pos)
    : Weapon(itemName, attack, pos) {}

/**
 * @brief Getter for the class name.
 * @return the class name.
 */
std::string Sword::getClassName() const { return "Sword"; }
    
//|================================|Class Bow|======================================|
    
/**
 * @brief Constructor of the Bow class.
 * @param itemName the bow's name.
 * @param attack the attack points of the bow.
 * @param range the range of the bow (in blocks).
 * @param pos the position of the bow on the board.
 */
Bow::Bow(const std::string& itemName, double attack, double range, Position pos)
    : Weapon(itemName, attack, pos), range(range) {
    if (range < 0) {
        std::cerr << "Range cannot be negative. Setting to 0." << std::endl;
        range = 3; //Default range 
    }
}

/**
 * @brief Getter for the range stat.
 * @return the range of the Bow item.
 */
double Bow::getRange() const { return range; }

/**
 * @brief Setter for the range stat.
 * @param newRange the new range stat of the Bow item.
 */
void Bow::setRange(double newRange) {
    if (newRange < 0) {
        std::cerr << "Range cannot be negative. Setting to 0." << std::endl;
        newRange = 3; //Default range 
    }
    range = newRange;
}

/**
 * @brief Getter for the class name.
 * @return the class name.
 */
std::string Bow::getClassName() const { return "Bow"; }
