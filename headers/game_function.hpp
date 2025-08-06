/*-Header file of src/game_function.cpp-*/
#pragma once
#include "classes.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.hpp"

#ifndef GAMEFUNCTION_HPP
#define GAMEFUNCTION_HPP

class Board;

void HealPlayer(std::shared_ptr<Player> player,int amount);
void HealPlayerOnItem(std::shared_ptr<Player> player,Board& board,Position pos);

void MoveDirection(std::shared_ptr<Entity> entity,
				    Direction direction,
					Board& board,
					SDL_Renderer* renderer,
					TTF_Font* font,
					SDL_Texture* playerTexture,
					SDL_Texture* mobTexture);
               
void CollectItem(std::shared_ptr<Player> player, Board& board,Position pos);
bool IsPlayerNearMob(Player* player, Board& board);
Mob* getNearMob(Player* player,Board& board);
bool isMobAt(Position pos,Board& board);

#endif
