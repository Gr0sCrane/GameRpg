#define SDL_MAIN_HANDLED
#include <iostream>
#include "main.hpp"
#include "input.cpp"

int main(int argc, char *argv[]) {

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
