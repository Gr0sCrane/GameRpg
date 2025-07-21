#include <iostream>
#include "combat.hpp"

SDL_Color white = {255, 255, 255, 255};
SDL_Color green = {15,255,0,0};
SDL_Color red = {155,0,0,0};
SDL_Color yellow = {255, 255, 0, 255};

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (!surface) return;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect destRect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void displayCombat(SDL_Renderer* renderer, TTF_Font* font,
                   SDL_Texture* playerTexture, SDL_Texture* mobTexture,
                   std::shared_ptr<Player> player, std::shared_ptr<Mob> mob,Turn currentTurn,
                    int selectedIndex) {
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Affiche les sprites
    SDL_Rect playerRect = {100, 200, 128, 128};
    SDL_Rect mobRect = {400, 200, 128, 128};
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);
    SDL_RenderCopy(renderer, mobTexture, NULL, &mobRect);

     // HUD - HP
    std::string playerHpText = "Player HP: " + std::to_string((int)player->getStats().hp) +
                               "/" + std::to_string(player->getStats().maxHp);
    std::string mobHpText = "Enemy HP: " + std::to_string((int)mob->getStats().hp) +
                            "/" + std::to_string(mob->getStats().maxHp);
    renderText(renderer,font,playerHpText,100,150,green);
    renderText(renderer,font,mobHpText,400,150,red);


    if (currentTurn == Turn::MOB){
        renderText(renderer,font,"Enemy is attacking",250,100,red);
    } else {
        renderText(renderer,font,"Player turn",250,100,white);
    }

    std::vector<std::string> options = {"Attack","Protect","Inventory","Run"};
    int menuX = 100;
    int menuY = 400;

    for (int i = 0; i < options.size(); i++){
        //TODO: selectedIndex comparing an int while being a size_t type
        std::string line = (i == selectedIndex) ? "> " + options[i] : "  " + options[i];
        SDL_Color color = (i == selectedIndex) ? yellow : white;
        renderText(renderer, font, line, menuX + i * 200, menuY, color);
    }

    DisplayRect(renderer,menuX,menuY,options);
    SDL_RenderPresent(renderer);
}

void DisplayRect(SDL_Renderer* renderer,int x, int y,const std::vector<std::string>& options){

    int SpacingX = 200;
    int padding = 10;

     for (int i = 0; i < options.size(); ++i) {
        int rectX = x + i * SpacingX - padding;
        int rectY = y - padding;
        int rectW = 100 + 2 * padding;
        int rectH = 30 + 2 * padding;

        SDL_Rect rect = {rectX, rectY, rectW, rectH};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void StartFight(Board& board, std::shared_ptr<Player> player, std::shared_ptr<Mob> mob,
                SDL_Renderer* renderer, TTF_Font* font,
                SDL_Texture* playerTexture, SDL_Texture* mobTexture) {

    bool isCombatOver = false;
    Turn currentTurn = Turn::PLAYER;
    player->setPlayerProtecting(false);
    int selectedIndex = 0;


    SDL_Event e;

    std::vector<std::string> options = {"Attack", "Protect", "Inventory", "Run"};

    while (!isCombatOver) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            }

            if (currentTurn == Turn::PLAYER && e.type == SDL_KEYDOWN) {
                if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    selectedIndex = (selectedIndex + 1) % options.size();
                } else if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                    selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
                } else if (e.key.keysym.scancode == SDL_SCANCODE_RETURN) {

                    std::string choice = options[selectedIndex];

                    if (choice == "Attack") {
                        player->attack(mob);
                        player->setPlayerProtecting(false);
                        currentTurn = Turn::MOB;
                    } else if (choice == "Protect") {
                        player->setPlayerProtecting(true);
                        currentTurn = Turn::MOB;
                    } else if (choice == "Inventory") {
                        // TODO: Afficher sous-menu inventaire ici
                        std::cout << "Inventory selected (à implémenter)" << std::endl;
                    } else if (choice == "Run") {
                        std::cout << "Player tried to run..." << std::endl;
                        isCombatOver = true;
                    }
                }
            }
        }

        displayCombat(renderer, font, playerTexture, mobTexture, player, mob, currentTurn, selectedIndex);

        if (mob->getStats().hp <= 0) { // Enemy defeated
            isCombatOver = true;
            player->getStats().gainXp(mob->getStats().level * 3); // Player gain Xp 
            break;
        } else if (player->getStats().hp <= 0) { // Player defeated
            isCombatOver = true;
            break;
        }
        
        // Enemy Turn
        if (currentTurn == Turn::MOB) {
            SDL_Delay(500);
            mob->attackPlayer(player);
            currentTurn = Turn::PLAYER;
            SDL_Delay(500);
        }

    }
}

//TODO: l'IG + inventaire et meilleur systeme de run. (trop simple pour l'instant)


