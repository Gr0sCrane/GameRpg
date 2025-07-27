#define SDL_MAIN_HANDLED
#include <iostream>
#include "main.hpp"
#include "input.cpp"

int main(int argc, char *argv[]) {

	Board board;

	auto player = std::make_shared<Player>(kDefault_pos);
    auto Mob1 = std::make_shared<Mob>("Teto", Stats(50,2), kDefault_pos);
    auto Mob2 = std::make_shared<Mob>("Miku", Stats(50,2), kDefault_pos);
    auto Mob3 = std::make_shared<Mob>("Rarez",Stats(50,2),kDefault_pos);
    auto Mob4 = std::make_shared<Mob>("Neru",Stats(50,2),kDefault_pos);
    auto Sword_ = std::make_shared<Sword>("Sword", 5, kDefault_pos);
    auto Bow_ = std::make_shared<Bow>("Bow", 2, 5, kDefault_pos);
    auto Heal_ = std::make_shared<Heal>("Heal", 25, kDefault_pos);
	auto Heal2_ = std::make_shared<Heal>("Heal", 25, kDefault_pos);

	board.setEntity(Position(kBoardSize/2,kBoardSize/2), player);
    board.setEntity(Position(2,16), Heal_);
    board.setEntity(Position(5,10),Heal2_);
    board.setEntity(Position(10,13),Mob3);
    board.setEntity(Position(2,2),Mob4);
    
    Position randomPos = generateRandomPosition(kBoardSize, board);
    Position randomPos2 = generateRandomPosition(kBoardSize, board);
    Position randomPosItem = generateRandomItemPosition(kBoardSize, board);
    Position randomPosBow = generateRandomItemPosition(kBoardSize, board);
    
    board.setEntity(Position(randomPos.x,randomPos.y), Mob1);
    board.setEntity(Position(randomPos2.x, randomPos2.y), Mob2);
    board.setEntity(Position(randomPosItem.x, randomPosItem.y), Sword_);
    board.setEntity(Position(randomPosBow.x, randomPosBow.y), Bow_);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("assets/fonts/IMPACT.ttf", 20);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font* TitleFont = TTF_OpenFont("assets/fonts/Beach-Ball.ttf",30);
    if (!TitleFont) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface* PlayerSurface = IMG_Load("assets/images/Miku_forgor.png");
    if (!PlayerSurface) {
        std::cerr << "Failed to load player image: " << IMG_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface* SwordSurface = IMG_Load("assets/images/minecraft_sword.jpg");
    if (!SwordSurface) {
        std::cerr << "Failed to load sword image: " << IMG_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface* BowSurface = IMG_Load("assets/images/Minecraft_bow.jpg");
    if (!BowSurface) {
        std::cerr << "Failed to load bow image: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(SwordSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface* MobSurface = IMG_Load("assets/images/sinje.jpg");
    if (!MobSurface) {
        std::cerr << "Failed to load mob image: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(BowSurface);
        SDL_FreeSurface(SwordSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface* HealSurface = IMG_Load("assets/images/Heal_potion.png");
    if (!HealSurface) {
        std::cerr << "Failed to load heal image: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(MobSurface);
        SDL_FreeSurface(BowSurface);
        SDL_FreeSurface(SwordSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Mini game RPG AlphaTest",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          900, 608, //608x608 pour un plateau de 19x19 avec des tuiles de 32x32
                                          0);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, PlayerSurface);
    SDL_Texture* swordTexture = SDL_CreateTextureFromSurface(renderer, SwordSurface);
    SDL_Texture* bowTexture = SDL_CreateTextureFromSurface(renderer, BowSurface);
    SDL_Texture* mobTexture = SDL_CreateTextureFromSurface(renderer, MobSurface);
    SDL_Texture* healTexture = SDL_CreateTextureFromSurface(renderer, HealSurface);
    SDL_FreeSurface(PlayerSurface); // libère la surface après avoir créé la texture
    SDL_FreeSurface(SwordSurface);
    SDL_FreeSurface(BowSurface);
    SDL_FreeSurface(MobSurface);
    SDL_FreeSurface(HealSurface);


    // Set the Gamestate in Title screen
    GameState currentState = GameState::TITLE;
    Uint32 lastEnemyUpdate = SDL_GetTicks();
    const Uint32 enemyUpdateInterval = 800;

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            
            Uint32 currentTime = SDL_GetTicks();
            if (currentState == GameState::FREE && currentTime - lastEnemyUpdate > enemyUpdateInterval) {
                setAlgorithm(player, board, renderer, font, playerTexture, mobTexture);
                lastEnemyUpdate = currentTime;
            }

            if (e.type == SDL_QUIT){
                quit = 1;
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                TTF_CloseFont(font);
                TTF_CloseFont(TitleFont);
                TTF_Quit();
                SDL_Quit();
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
                        quit = true;
                    }
                }
            }
		}
        if (currentState == GameState::TITLE){
            if (is_key_pressed(SDL_SCANCODE_SPACE)){
                currentState = GameState::FREE;
            }
            board.drawTitleScreen(renderer,TitleFont);
            SDL_RenderPresent(renderer);
            SDL_Delay(20);
        }
        else if (currentState == GameState::PAUSE){
            board.drawPauseScreen(renderer,TitleFont);
            SDL_RenderPresent(renderer);
            SDL_Delay(20);
        }
        else if (currentState == GameState::FREE){

            for (const auto& [key, dir] : keyToDirection) {
                if (is_key_pressed(key)) {
                    MoveDirection(player, dir, board, renderer, font, playerTexture, mobTexture);
                }
            }
		    board.DrawBoard(renderer, playerTexture,swordTexture,bowTexture,mobTexture,healTexture);
		    board.DrawInfo(renderer, player.get());
            board.renderPlayerInfo(renderer,font,player.get(),board);
		    SDL_RenderPresent(renderer);
            SDL_Delay(80);
        }

        // UPDATE
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastEnemyUpdate > enemyUpdateInterval) {
            setAlgorithm(player, board, renderer, font, playerTexture, mobTexture);
            lastEnemyUpdate = currentTime;
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_CloseFont(TitleFont);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
