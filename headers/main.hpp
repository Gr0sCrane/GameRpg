#include <iostream>
#include <vector>
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include "game_function.hpp"
#include "entity_spawn.hpp"
#include "combat.hpp"
#include "algorithm.hpp"

const Position kDefault_pos = Position(0,0);

const std::unordered_map<SDL_Scancode, Direction> keyToDirection = {
    {SDL_SCANCODE_UP, Direction::UP},
    {SDL_SCANCODE_DOWN, Direction::DOWN},
    {SDL_SCANCODE_LEFT, Direction::LEFT},
    {SDL_SCANCODE_RIGHT, Direction::RIGHT}
};



