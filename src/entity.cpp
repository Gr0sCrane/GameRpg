#include <iostream>
#include "entity.hpp"

//|================================|Class Entity|======================================|

/**
 * @brief Constructor of the entity class.
 * @param t the type of the entity
 * @param hp the health points of the entity.
 * @param attack the attack points of the entity.
 * @param pos the position of the entity.
 * @see EntityType
 */
Entity::Entity(EntityType t, double hp, double attack, Position pos) :
    type(t), hp(hp), attack(attack), Pos(pos) {}

Entity::~Entity() = default;


/**
 * @brief Change the position of the entity.
 * @param pos the new position.
 */
void Entity::setPosition(Position pos) {
    if (pos.x < 0 || pos.y < 0) {
        std::cout << "Position cannot be negative. Setting to (0, 0)." << std::endl;
        Pos = Position(0,0);
    } else {
        Pos = Position(pos.x,pos.y);
    }
}

/**
 * @brief Getter for the entity's position.
 * @return the position of the entity on the board.
 */
Position Entity::getPosition() {
    return Pos;
}

/**
 * @brief Getter for the type of the entity
 * @see EntityType
 * @return the type of the entity.
 */
EntityType Entity::getType() const { return type; }

/**
 * @brief Getter for the class name.
 * @return the name of the class.
 */
std::string Entity::getClassName() const {return "Entity";}