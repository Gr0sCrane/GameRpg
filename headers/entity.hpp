#include <iostream>
#include "position.hpp"

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
