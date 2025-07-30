/*-Header file of src/algorithm.cpp-*/
#include <iostream>
#include <math.h>
#include <random>
#include "player.hpp"
#include "mob.hpp"
#include "board.hpp"

int calculateDistance(std::shared_ptr<Mob> mob,std::shared_ptr<Player> player);

void initAlgorithm(std::shared_ptr<Player> player,Board& board,SDL_Renderer* renderer,
    TTF_Font* font,SDL_Texture* playerTexture,SDL_Texture* mobTexture);