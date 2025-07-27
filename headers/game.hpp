#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include "board.hpp"
#include "combat.hpp"
#include "entity_spawn.hpp"
#include "algorithm.hpp"

const std::unordered_map<SDL_Scancode, Direction> keyToDirection = {
    {SDL_SCANCODE_UP, Direction::UP},
    {SDL_SCANCODE_DOWN, Direction::DOWN},
    {SDL_SCANCODE_LEFT, Direction::LEFT},
    {SDL_SCANCODE_RIGHT, Direction::RIGHT}
};

struct Game {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    TTF_Font* font = nullptr;
    TTF_Font* titleFont = nullptr;

    SDL_Surface* PlayerSurface = nullptr;
    SDL_Surface* SwordSurface = nullptr;
    SDL_Surface* BowSurface = nullptr;
    SDL_Surface* MobSurface = nullptr;
    SDL_Surface* HealSurface = nullptr;

    SDL_Texture* playerTexture = nullptr;
    SDL_Texture* swordTexture = nullptr;
    SDL_Texture* bowTexture = nullptr;
    SDL_Texture* mobTexture = nullptr;
    SDL_Texture* healTexture = nullptr;

    std::shared_ptr<Player> player;
    Board board;

    GameState currentState = GameState::TITLE;
    Uint32 lastEnemyUpdate = 0;
    const Uint32 enemyUpdateInterval = 800;

    bool initRender();
    void init();
    void run();
    void quit();
};