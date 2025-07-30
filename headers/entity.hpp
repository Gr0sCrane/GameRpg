/*-Header file of src/entity.cpp-*/
#include <iostream>
#include "position.hpp"

/**
 * @enum EntityType
 * @brief represent the Type of the Entity
 * @return 4 type: PLAYER, MOB, ITEM, VOID
 */
enum class EntityType {
    /// player entity
    PLAYER,
    /// enemy entity
    MOB,
    /// item entity
    ITEM,
    /// void entity
    VOID
};

/**
 * @class Entity
 * represent an entity
 * 
 */
class Entity {
    private:
    EntityType type;
    double hp;
    double attack;
    Position Pos;
    public:
    Entity(EntityType t, double hp, double attack, Position pos);
    virtual ~Entity();
    
    virtual std::string getClassName() const;
    
    void setPosition(Position pos);
    Position getPosition();
    
    EntityType getType() const;
};
