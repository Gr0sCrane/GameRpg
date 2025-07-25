#include <iostream>
#include "player.hpp"
#include "mob.hpp"
#include "board.hpp"

int calculateDistance(std::shared_ptr<Mob> mob,std::shared_ptr<Player> player);
void initEnemyAlgortihm(Board& board,std::shared_ptr<Player> player);