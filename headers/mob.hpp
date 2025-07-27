#pragma once
#include <iostream>
#include "classes.hpp"
#include "player.hpp"
#include "board.hpp"

enum class Enemystate {
    PATROL, // the enemy is free to move on the board
    CHASE // the enemy chase the nearest player
};

class Mob : public Entity, public std::enable_shared_from_this<Mob> {
private:
    std::string mobname;
    Stats stats;
    Inventory inventory;
    Enemystate currentState;
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
    void chase(std::shared_ptr<Player> player,int distance,Board& board,
                SDL_Renderer* renderer,TTF_Font* font,SDL_Texture* playerTexture,
                SDL_Texture* mobTexture);
};