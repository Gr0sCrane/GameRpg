/**
 * This game is a side project made by me just for fun and to learn programming
 * and C++. You can use it for whatever you want. If you want to use it and make
 * it better, you can. If you are better than me at programming you can change
 * it and upgrade it.
 * Thank you for reading this.
 * Mouad.
 */
#define SDL_MAIN_HANDLED
#include "game.hpp"
#include <iostream>

/**
 * Main function
 */
int main() {

  Game game;
  if (!game.initRender()) {
    std::cout << "+ Renderer failed to load...<< \n";
    return 1;
  }
  game.init();
  game.run();
  game.quit();
  return 0;
}
