#include <iostream>
#include "entity.hpp"

//|================================|Class Entity|======================================|

Entity::Entity(EntityType t, double hp, double attack, Position pos) :
    type(t), hp(hp), attack(attack), Pos(pos) {}

Entity::~Entity() = default;

bool Entity::isAlive() const {
    return hp > 0;
}

void Entity::setPosition(Position pos) {
    if (pos.x < 0 || pos.y < 0) {
        std::cout << "Position cannot be negative. Setting to (0, 0)." << std::endl;
        Pos = Position(0,0);
    } else {
        Pos = Position(pos.x,pos.y);
    }
}

Position Entity::getPosition() {
    return Pos;
}

EntityType Entity::getType() const { return type; }
std::string Entity::getClassName() const {return "Entity";}