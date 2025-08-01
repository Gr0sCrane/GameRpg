#include "input.h"
#include <SDL_keyboard.h>

// * Checks if a key was pressed, scancode should be something like "SDL_SCANCODE_X"
bool is_key_pressed(int scancode){
    const Uint8* keys = SDL_GetKeyboardState(NULL); //gets keys only when asks for keypress, this way we don't check every frame for a keypress
    return keys[scancode];
}