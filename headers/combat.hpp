#include <iostream>
#include "board.hpp"
#include "input.h"

enum class GameState {
    FREE, // the player is free to move
    COMBAT, // Combat mode
    TITLE ,// Titlescreen
    PAUSE // pause mode (still in work)
};

enum class Turn{
    PLAYER,
    MOB
};

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color);

void displayCombat(SDL_Renderer* renderer, TTF_Font* font,
                   SDL_Texture* playerTexture, SDL_Texture* mobTexture,
                   std::shared_ptr<Player> player, std::shared_ptr<Mob> mob,Turn currentTurn,
                    int selectedIndex);

void DisplayRect(SDL_Renderer* renderer,int x,int y,const std::vector<std::string>& options);

void StartFight(Board& board,std::shared_ptr<Player> player, std::shared_ptr<Mob> mob
                ,SDL_Renderer* renderer, TTF_Font* font,SDL_Texture* Playertexture,SDL_Texture* MobTexture);