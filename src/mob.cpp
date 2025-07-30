#include <iostream>
#include "mob.hpp"

/**
 * @brief Constructor of the mob class.
 * @param name the name of the enemy.
 * @param Stats the statistics of the enemy (hp, attack, defense).
 * @param pos the position of the enemy on the board.
 */
Mob::Mob(const std::string& name,Stats Stats,Position pos) : Entity(EntityType::MOB,Stats.hp,Stats.attack,pos), mobname(name),
    stats(Stats),
    inventory() {}

/**
 * @brief Getter for the Class name used for recognizing the entity.
 * @return the name of the class.
 */
std::string Mob::getClassName() const { return "Mob"; }

/**
 * @brief Getter for the enemy's name.
 * @return name of the enemy.
 */
std::string Mob::getMobName() const { return mobname; }

/**
 * @brief Setter for the enemy's name.
 * @param newName the new name of the enemy.
 */
void Mob::setMobName(const std::string& newName) { mobname = newName; }

/**
 * @brief Getter for the enemy's statistics.
 * @return the Statistics of the enemy.
 */
Stats& Mob::getStats() {
    return stats;
}

/**
 * @brief This function is used by the enemy to attack the player
 * during a fight.
 * 
 * if the player is protecting, the damage is reduced using the player's defense.
 * 
 * if not then the player get 100% of the damage given by the enemy.
 * 
 * @param player the targeted player.
 */
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

/**
 * @brief Getter for the current state of the enemy.
 * @return the state of the enemy.
 * @see EnemyState
 */
Enemystate Mob::getCurrentState() const {
    return currentState;
}

/**
 * @brief Set the current state to CHASE.
 * @see EnemyState
 */
void Mob::setChase(){
    currentState = Enemystate::CHASE;
}

/**
 * @brief Set the current state to PATROL.
 * @see EnemyState
 */
void Mob::setPatrol(){
    currentState = Enemystate::PATROL;
}

/**
 * @brief The enemy will move freely on the board using randomly generated direction
 * @param board the game board.
 * @param renderer the renderer (SDL).
 * @param font the font used for texts.
 * @param playerTexture the texture of the player.
 * @param mobTexture the texture of the enemy.
 */
void Mob::patrol(Board& board,SDL_Renderer* renderer,TTF_Font* font,SDL_Texture* playerTexture,
                SDL_Texture* mobTexture){
    Direction dir = getRandDir();
    MoveDirection(shared_from_this(),dir,board,renderer,font,playerTexture,mobTexture);
}

/**
 * @brief The enemy will try to purchase the player on the board using an algorithm.
 * 
 * the enemy purchase the player as long as the distance between him and the player is below or equals to 5.
 * @param board the game board.
 * @param renderer the renderer (SDL).
 * @param font the font used for texts.
 * @param playerTexture the texture of the player.
 * @param mobTexture the texture of the enemy.
 */
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