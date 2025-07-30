/*-Header file of src/combat.cpp-*/
#include <iostream>
#include "board.hpp"
#include "input.h"
#include "player.hpp"
#include "mob.hpp"
#include <random>

/**
 * @enum GameState
 * @brief indicate the state of the game.
 * @return 5 mode: FREE, COMBAT, TITLE, PAUSE, GAMEOVER
 */
enum class GameState {
    /// the player is free to move
    FREE,
    /// Fight mode
    COMBAT,
    /// Title screen
    TITLE,
    /// Pause mode
    PAUSE,
    /// Game over, player is at 0 hp.
    GAMEOVER
};

/**
 * @enum Turn
 * @brief indicate in which turn is the fight occuring.
 * @return PLAYER or MOB
 */
enum class Turn{
    /// Player turn
    PLAYER,
    /// Enemy turn
    MOB
};

bool running(std::shared_ptr<Player> player);

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color);

void getItemInventory(std::shared_ptr<Player> player,SDL_Renderer* renderer,TTF_Font* font);

void displayCombat(SDL_Renderer* renderer, TTF_Font* font,
                   SDL_Texture* playerTexture, SDL_Texture* mobTexture,
                   std::shared_ptr<Player> player, std::shared_ptr<Mob> mob,Turn currentTurn,
                    int selectedIndex,bool isInventorySelected);

void DisplayRect(SDL_Renderer* renderer,int x,int y,const std::vector<std::string>& options);

void StartFight(Board& board,std::shared_ptr<Player> player, std::shared_ptr<Mob> mob
                ,SDL_Renderer* renderer, TTF_Font* font,SDL_Texture* Playertexture,SDL_Texture* MobTexture);