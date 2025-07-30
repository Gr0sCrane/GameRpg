/*-Header file of src/mob.cpp-*/ 
#pragma once
#include <iostream>
#include "classes.hpp"
#include "player.hpp"
#include "board.hpp"

/**
 * @enum EnemyState
 * @brief represent the current state of the enemy.
 */
enum class Enemystate {

    /// the enemy is free to move on the board
    PATROL,
    /// the enemy chase the nearest player
    CHASE
};

/**
 * @class Mob
 * @brief Represent a enemy
 * 
 */
class Mob : public Entity, public std::enable_shared_from_this<Mob> {
private:
    std::string mobname;
    Stats stats;
    Inventory inventory;
    Enemystate currentState; // the current state of the enemy.
public:
    Mob(const std::string& name,Stats stats,Position pos);
    std::string getMobName() const;
    void setMobName(const std::string& newName);
    virtual std::string getClassName() const override;
    Stats& getStats();
    const Stats& getStats() const;
    void attackPlayer(std::shared_ptr<Player> player);
    Enemystate getCurrentState() const;
    void setPatrol();
    void setChase();
    void patrol(Board& board,SDL_Renderer* renderer,TTF_Font* font,SDL_Texture* playerTexture,
                SDL_Texture* mobTexture);
    void chase(std::shared_ptr<Player> player,Board& board,
                SDL_Renderer* renderer,TTF_Font* font,SDL_Texture* playerTexture,
                SDL_Texture* mobTexture);
};