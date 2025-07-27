#include <iostream>
#include "mob.hpp"

Mob::Mob(const std::string& name,Stats Stats,Position pos) : Entity(EntityType::MOB,Stats.hp,Stats.attack,pos), mobname(name),
    stats(Stats),
    inventory() {}
std::string Mob::getClassName() const { return "Mob"; }
std::string Mob::getMobName() const { return mobname; }
void Mob::setMobName(const std::string& newName) { mobname = newName; }

Stats& Mob::getStats() {
    return stats;
}

const Stats& Mob::getStats() const {
    return stats;
}

void Mob::attackPlayer(std::shared_ptr<Player> player) {
    double attackAmount = getStats().attack;
    double finalDamage;

    if (player->isPlayerProtecting()) {
        finalDamage = player->protect(attackAmount);
    } else {
        double defense = player->getStats().defense;
        finalDamage = attackAmount * (100.0 / (100.0 + defense));
    }

    double playerHp = player->getStats().hp;
    playerHp -= finalDamage;
    if (playerHp < 0) playerHp = 0;

    player->getStats().hp = playerHp;
}

Enemystate Mob::getCurrentState() const {
    return currentState;
}

void Mob::setChase(){
    currentState = Enemystate::CHASE;
}

void Mob::setPatrol(){
    currentState = Enemystate::PATROL;
}

void Mob::patrol(Board& board,SDL_Renderer* renderer,TTF_Font* font,SDL_Texture* playerTexture,
                SDL_Texture* mobTexture){
    Direction dir = getRandDir();
    MoveDirection(shared_from_this(),dir,board,renderer,font,playerTexture,mobTexture);
}

void Mob::chase(std::shared_ptr<Player> player,Board& board,
                SDL_Renderer* renderer,TTF_Font* font,SDL_Texture* playerTexture,
                SDL_Texture* mobTexture){

    Position mobPos = getPosition();
    Position playerPos = player->getPosition();
    
    if (mobPos.x < playerPos.x){
        MoveDirection(shared_from_this(),Direction::DOWN,board,renderer,font,playerTexture,mobTexture);
    }
    if (mobPos.y < playerPos.y){
        MoveDirection(shared_from_this(),Direction::RIGHT,board,renderer,font,playerTexture,mobTexture);
    }
    if (mobPos.x > playerPos.x){
        MoveDirection(shared_from_this(),Direction::UP,board,renderer,font,playerTexture,mobTexture);
    }
    if (mobPos.y > playerPos.y){
        MoveDirection(shared_from_this(),Direction::LEFT,board,renderer,font,playerTexture,mobTexture);
    }
}