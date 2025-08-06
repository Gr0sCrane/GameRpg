/*-Header file of src/game.cpp-*/
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "board.hpp"
#include "combat.hpp"
#include "entity_spawn.hpp"
#include "algorithm.hpp"

/**
 * Check inputs and give a direction
 * @return a direction
 * @see Enum Direction
 */
const std::unordered_map<SDL_Scancode, Direction> keyToDirection = {
    /// arrows
    {SDL_SCANCODE_UP,    Direction::UP},
    {SDL_SCANCODE_DOWN,  Direction::DOWN},
    {SDL_SCANCODE_LEFT,  Direction::LEFT},
    {SDL_SCANCODE_RIGHT, Direction::RIGHT},

    // WASD (QWERTY)
    {SDL_SCANCODE_W, Direction::UP},
    {SDL_SCANCODE_A, Direction::LEFT},
    {SDL_SCANCODE_S, Direction::DOWN},
    {SDL_SCANCODE_D, Direction::RIGHT},

    // ZQSD (AZERTY)
    {SDL_SCANCODE_Z, Direction::UP},
    {SDL_SCANCODE_Q, Direction::LEFT}
};

/**
 * @struct Game
 * Contains all the assets and game functions required to run the game.
 * @param window the main window (SDL).
 * @param renderer a structure representing rendering state (SDL).
 * @param font the font used to write texts -> from assets/fonts/
 * @param titlefont another font used to write texts -> assets/fronts/
 * 
 * @param PlayerSurface, playertexture the texture of the player -> assets/images/
 * @param SwordSurface, swordtexture the texture of swords items -> assets/images/
 * @param BowSurface, bowTexture the texture of bows items -> assets/images/
 * @param MobSurface, mobtexture the texture of enemies -> assets/images/
 * @param HealSurface, healTexture the texture of heals items -> assets/images/
 * 
 * @param player the player.
 * @param board the main board
 * 
 * @param currentState the current state of the Game: FREE, COMBAT, TITLE, PAUSE and GAMEOVER.
 * @param lastEnemyUpdate the last enemy update used for the update loop.
 * @param enemyUpdateInterval the interval between an update.
 */
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
