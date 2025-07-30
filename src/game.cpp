#include <iostream>
#include "game.hpp"

/**
 * @brief Init the SDL and load all the texture of the game.
 * @return True if it succeed, false if not.
 */
bool Game::initRender(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return false;
    }
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    font = TTF_OpenFont("assets/fonts/IMPACT.ttf", 20);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    titleFont = TTF_OpenFont("assets/fonts/Beach-Ball.ttf",30);
    if (!titleFont) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    PlayerSurface = IMG_Load("assets/images/Miku_forgor.png");
    if (!PlayerSurface) {
        std::cerr << "Failed to load player image: " << IMG_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    SwordSurface = IMG_Load("assets/images/minecraft_sword.jpg");
    if (!SwordSurface) {
        std::cerr << "Failed to load sword image: " << IMG_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    BowSurface = IMG_Load("assets/images/Minecraft_bow.jpg");
    if (!BowSurface) {
        std::cerr << "Failed to load bow image: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(SwordSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    MobSurface = IMG_Load("assets/images/sinje.jpg");
    if (!MobSurface) {
        std::cerr << "Failed to load mob image: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(BowSurface);
        SDL_FreeSurface(SwordSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    HealSurface = IMG_Load("assets/images/Heal_potion.png");
    if (!HealSurface) {
        std::cerr << "Failed to load heal image: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(MobSurface);
        SDL_FreeSurface(BowSurface);
        SDL_FreeSurface(SwordSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    /*DEBUG CONSOLE*/
    std::cout<< "+ Loaded all images..." << "\n";

    window = SDL_CreateWindow("Mini game RPG AlphaTest",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          900, 608, //608x608 pour un plateau de 19x19 avec des tuiles de 32x32
                                          0);
    if (!window) {
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    /*DEBUG CONSOLE*/
    std::cout<<"+ Loaded window and renderer..."<<"\n";

    playerTexture = SDL_CreateTextureFromSurface(renderer, PlayerSurface);
    swordTexture = SDL_CreateTextureFromSurface(renderer, SwordSurface);
    bowTexture = SDL_CreateTextureFromSurface(renderer, BowSurface);
    mobTexture = SDL_CreateTextureFromSurface(renderer, MobSurface);
    healTexture = SDL_CreateTextureFromSurface(renderer, HealSurface);
    SDL_FreeSurface(PlayerSurface);
    SDL_FreeSurface(SwordSurface);
    SDL_FreeSurface(BowSurface);
    SDL_FreeSurface(MobSurface);
    SDL_FreeSurface(HealSurface);

    /*DEBUG CONSOLE*/
    std::cout<<"+ Loaded all textures..."<<"\n";

    return true;
}

/**
 * @brief Init the player, enemy spawns and items spawn.
 */
void Game::init(){

    player = std::make_shared<Player>(kDefault_pos);

    spawnEnemy(board,player);

    board.setEntity(Position(kBoardSize/2,kBoardSize/2),player);

    auto Sword_ = std::make_shared<Sword>("Sword",5,kDefault_pos);
    Position randomPosItem = generateRandomItemPosition(kBoardSize, board);
    board.setEntity(Position(randomPosItem.x, randomPosItem.y), Sword_);

    /*DEBUG CONSOLE*/
    std::cout<<"+ Loaded the player and the entities..."<<"\n";

}

/**
 * @brief Closes the SDL and clean up everything.
 */
void Game::quit(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_CloseFont(titleFont);
    TTF_Quit();
    SDL_Quit();

    /*DEBUG CONSOLE*/
    std::cout<<"+ Game closed..."<<"\n";
}

/**
 * @brief The main loop.
 * 
 * Start the game in Title screen, if the player press ENTER, the game start. 
 * If the player press ESCAPE the game enter in PAUSE mode. To leave this mode press ENTER.
 * 
 * In FREE mode, the player can move on the board using the arrows and can collect items or start a fight touching an enemy.
 * Each 800 ms the game update.
 * 
 * If the player have low hp, a heal item spawn randomly on the board.
 * 
 * If the board contains no enemies, the game generated 3 new enemies with scaled stats based on the player level.
 */
void Game::run(){
    // Set the Gamestate in Title screen
    currentState = GameState::TITLE;
    lastEnemyUpdate = SDL_GetTicks();

    SDL_Event e;
    int end = 0;
    while (!end) {
        while (SDL_PollEvent(&e)) {
            
            if (e.type == SDL_QUIT){
                end = 1;
                quit();
            }
            else if (e.type == SDL_KEYDOWN) {
                SDL_Scancode key = e.key.keysym.scancode;

                if (currentState == GameState::TITLE && key == SDL_SCANCODE_SPACE) {
                    currentState = GameState::FREE;
                }
                else if (currentState == GameState::FREE && key == SDL_SCANCODE_ESCAPE) {
                    currentState = GameState::PAUSE;
                    std::cout << "Game Paused" << std::endl;
                }
                else if (currentState == GameState::PAUSE) {
                    if (key == SDL_SCANCODE_ESCAPE) {
                        currentState = GameState::FREE;
                        std::cout << "Resume Game" << std::endl;
                    } else if (key == SDL_SCANCODE_RETURN) {
                        end = true;
                    }
                } else if (currentState == GameState::GAMEOVER){
                    board.drawGameOverScreen(renderer,titleFont);
                    if (key == SDL_SCANCODE_RETURN){
                        end = true;
                    }
                    SDL_RenderPresent(renderer);
                }
            }
		}
        if (currentState == GameState::TITLE){
            if (is_key_pressed(SDL_SCANCODE_SPACE)){
                currentState = GameState::FREE;
            }

            board.drawTitleScreen(renderer,titleFont);
            SDL_RenderPresent(renderer);
            SDL_Delay(20);
        }
        else if (currentState == GameState::PAUSE){

            board.drawPauseScreen(renderer,titleFont);
            SDL_RenderPresent(renderer);
            SDL_Delay(20);

        }
        else if (currentState == GameState::FREE){

            if (player->getStats().hp == 0){
                currentState = GameState::GAMEOVER;
            }

            // UPDATE
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - lastEnemyUpdate > enemyUpdateInterval) {
                initAlgorithm(player, board, renderer, font, playerTexture, mobTexture);
                lastEnemyUpdate = currentTime;
            }

            for (const auto& [key, dir] : keyToDirection) {
                if (is_key_pressed(key)) {
                    MoveDirection(player, dir, board, renderer, font, playerTexture, mobTexture);
                }
            }

            if(board.getEnemiesInBoard().empty()){
                spawnEnemy(board,player);
            }

            spawnHeal(board,player);

		    board.DrawBoard(renderer, playerTexture,swordTexture,bowTexture,mobTexture,healTexture);
		    board.DrawInfo(renderer, player.get());
            board.renderPlayerInfo(renderer,font,player.get(),board);
		    SDL_RenderPresent(renderer);
            SDL_Delay(80);
        }

    }
}
