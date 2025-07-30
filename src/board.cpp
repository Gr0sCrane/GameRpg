#include "board.hpp"
#include "mob.hpp"
#include <iostream> 

/**
 * @brief Determine a random direction.
 * 
 * Used for the enemy's algoritm in the PATROL state.
 * @see Mob.cpp
 * 
 * @return a direction chosed randomly.
 */
Direction getRandDir(){
    int nbr = rand() % 4;

    switch (nbr)
    {
    case 0:
        return Direction::DOWN;
        break;
    case 1:
        return Direction::UP;
        break;
    case 2:
        return Direction::LEFT;
        break;
    case 3:
        return Direction::RIGHT;
        break;
    
    default:
        return Direction::NONE;
        break;
    }
}

//|==========================|Class Board|===============================================|

/**
 * @brief Constructor of the Board class.
 */
Board::Board() {}

/**
 * @brief Destructor of the Board class.
 */
Board::~Board() = default;

/**
 * @brief Sets an entity at the position chosed and update the entity's position value.
 * 
 * @param pos the position where the entity will get placed.
 * @param entity the entity targeted.
 */
void Board::setEntity(Position pos, std::shared_ptr<Entity> entity) {
    if (pos.x >= 0 && pos.y < kBoardSize &&
        pos.y >= 0 && pos.y < kBoardSize) {

        if (entity) {
            entity->setPosition(pos);
            entities[pos] = entity;
        } else {
            entities.erase(pos);
        }

    } else {
        std::cerr << "Invalid Position:  (" << pos.x << ", " << pos.y << ")" << std::endl;
    }
}


/**
 * @brief Used to get the entity at the position given.
 * @return the entity at the position.
 * @param pos the position targeted.
 */
std::shared_ptr<Entity> Board::getEntityAt(Position pos) const {

    auto it = entities.find(pos);
    if (it != entities.end()){
        return it->second;
    }
    return nullptr;
}

/**
 * @brief Delete the entity at the position given.
 * @param pos the position targeted.
 */
void Board::DeleteEntity(Position pos) {

    auto it = entities.find(pos);
    if (it != entities.end()){
        entities.erase(it);
    }
}

/**
 * @brief Getter for the main array that contains all the entities.
 * @return the array of entities.
 */
std::unordered_map<Position,std::shared_ptr<Entity>> Board::getEntities() const {
    return entities;
}

/**
 * @brief Filter the main array of entities to get only the enemies.
 * @return an array of all the enemies.
 */
std::vector<std::pair<Position, std::shared_ptr<Entity>>> Board::getEnemiesInBoard() const{

    std::vector<std::pair<Position, std::shared_ptr<Entity>>> enemies;
    
    for (const auto &[position, entity] : entities)
    {
        if (entity->getType() == EntityType::MOB)
        {
            enemies.push_back({position, entity});
        }
    }
    return enemies;
}

/**
 * @brief Filter the main array of entities to get only the Heal items.
 * @return an array of all the Heal items.
 */
std::vector<std::pair<Position, std::shared_ptr<Entity>>> Board::getHealInBoard() const{

    std::vector<std::pair<Position, std::shared_ptr<Entity>>> Heals;
    
    for (const auto &[position, entity] : entities)
    {
        if (entity->getType() == EntityType::ITEM){
            if (dynamic_cast<Heal*>(entity.get())){
                Heals.push_back({position, entity});
            }
        }
    }
    return Heals;
}

/**
 * @brief Getter for the EntityType of the entity at the position given.
 * 
 * If the entity is not identified, it returns the EntityType VOID.
 * 
 * @see EntityType.
 * @param pos the position targeted.
 * 
 * @return the Entitytype of the entity at the position given.
 */
EntityType Board::getEntityType(Position pos) const {
    
    auto it = entities.find(pos);
    if (it != entities.end() && it->second){
        return it->second->getType();
    }
    return EntityType::VOID;
}

/**
 * @brief Indicate if the position given is walkable or not.
 *  This function is used for the enemy's algorithm.
 * 
 * @param pos the position targeted.
 * @return True if yes, false if not.
 */
bool Board::isWalkable(Position pos){
    if (getEntityType(pos) != EntityType::VOID && getEntityType(pos) != EntityType::PLAYER){
        return false;
    }
    return true;
}

/**
 * @brief Draws the board and all the textures of the player and enemies.
 * 
 * The function check with the EntityType to know wich texture to render and display on one case.
 * @param renderer the renderer (SDL).
 * @param Playertexture, SwordTexture, Bowtexture, MobTexture, HealTexture a texture of the entities.
 */
void Board::DrawBoard(SDL_Renderer* renderer,
    SDL_Texture* PlayerTexture,SDL_Texture* SwordTexture,
    SDL_Texture* BowTexture, SDL_Texture* MobTexture,
    SDL_Texture* HealTexture) const 
    {
    for (int i = 0; i < kBoardSize; ++i) {
        for (int j = 0; j < kBoardSize; ++j) {
            SDL_Rect cell = { j * kTilesize, i * kTilesize, kTilesize, kTilesize };

            Position pos(i,j); 

            auto it = entities.find(pos);
            std::shared_ptr<Entity> entity = (it != entities.end()) ? it->second : nullptr;

            if (entity && entity->getType() == EntityType::ITEM) {
                if (dynamic_cast<Sword*>(entity.get())) {
                    if (SwordTexture) {
                        SDL_RenderCopy(renderer, SwordTexture, nullptr, &cell);
                    } else {
                        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
                        SDL_RenderFillRect(renderer, &cell);
                    }
                    
                } else if (dynamic_cast<Bow*>(entity.get())) {
                    if (BowTexture) {
                        SDL_RenderCopy(renderer, BowTexture, nullptr, &cell);
                    } else {
                        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
                        SDL_RenderFillRect(renderer, &cell);
                    }
                }
                else if (dynamic_cast<Heal*>(entity.get())) {
                    if (HealTexture) {
                        SDL_RenderCopy(renderer, HealTexture, nullptr, &cell);
                    } else {
                        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
                        SDL_RenderFillRect(renderer, &cell);
                    }
                }
                else {
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // couleur par défaut pour les items
                }
                continue;
            }

            switch (getEntityType(pos)) {
            case EntityType::PLAYER:
                if (PlayerTexture) {
                    SDL_RenderCopy(renderer, PlayerTexture, nullptr, &cell);
                } else {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // fallback
                    SDL_RenderFillRect(renderer, &cell);
                }
                continue; // éviter de remplir deux fois la case

            case EntityType::MOB:
                if (MobTexture) {
                    SDL_RenderCopy(renderer, MobTexture, nullptr, &cell);
                } else {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
                continue;
            default:
                SDL_SetRenderDrawColor(renderer, 255, 255, 233, 0); // couleur pour les cases vides
                break;
            }

            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

/**
 * @brief Displays at the top right all the informations about the player.
 * 
 * Position, Health points, attack, defense, Xp, level...
 * 
 * @param renderer the renderer (SDL).
 * @param player the player.
 */
void Board::DrawInfo(SDL_Renderer* renderer, Player* player) const {
    if (!player) return;

    const int boardPixelsize = kBoardSize * kTilesize;

    SDL_Rect infoBox = {
        boardPixelsize, 0,
        900 - boardPixelsize, 608
    };

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &infoBox);
}

/**
 * @brief SDL function used for rendering texts on the screen using a font and colors.
 */
void Board::renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (!surface) return;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect destRect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

/**
 * @brief Displays at the top right all the informations about the player.
 * 
 * Position, Health points, attack, defense, Xp, level...
 * 
 * @param renderer the renderer (SDL).
 * @param player the player.
 * @param font the font used for texts.
 * @param board the gale board.
 */
void Board::renderPlayerInfo(SDL_Renderer* renderer, TTF_Font* font, Player* player, Board& board) {
    if (!player) return;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    int x = kBoardSize * kTilesize + 10;
    int y = 10;

    auto pos = player->getPosition();
    int nextXp = player->getStats().getXpToNxtLvl();
    std::ostringstream oss;

    oss << "Position: (" << pos.x << ", " << pos.y << ")";
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();

    oss << "HP: " << player->getStats().hp;
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();

    oss << "Attack: " << player->getStats().attack;
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();

    oss << "Defense: " << player->getStats().defense;
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();

    oss << "XP: " << player->getStats().xp << " | Level: " << player->getStats().level << "| next lvl in: "<< nextXp << " Xp";
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();
    
    renderText(renderer, font, "near Mob:", x , y, white);
    if (IsPlayerNearMob(player,board)) {
        auto mob = getNearMob(player,board);
        oss << " - " << mob->getMobName() << " (HP: " << mob->getStats().hp << ")";
        renderText(renderer, font, oss.str(), x + 100, y, red);
    } else {
        renderText(renderer, font, " - None", x + 100, y, white);
    }
    y += 50; oss.str(""); oss.clear();

    renderText(renderer, font, "Inventory:", x, y, white);
    y += 30;

    auto& inventory = player->getInventory();
    const auto& items = inventory.getItems();

    if (items.empty()) {
        renderText(renderer, font, " - (Empty)", x + 10, y, white);
    } else {
        for (const auto& item : items) {
            renderText(renderer, font, " - " + item->getName(), x + 10, y, white);
            y += 25;
        }
    }

}

/**
 * @brief Draws the title screen of the game.
 * @param renderer the renderer (SDL).
 * @param font the font used for texts.
 */
void Board::drawTitleScreen(SDL_Renderer* renderer, TTF_Font* font){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Color white = {255, 255, 255, 255};

    renderText(renderer, font, "Mini RPG Game", 350, 200,white);
    renderText(renderer, font, "Press SPACE to start", 300, 300,white);
    renderText(renderer,font,"personal project by Mouad, (it sucks)",420,570,white);
}

/**
 * @brief Draws the pause screen of the game.
 * @param renderer the renderer (SDL).
 * @param font the font used for texts.
 */
void Board::drawPauseScreen(SDL_Renderer* renderer,TTF_Font* font){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Color white = {255, 255, 255, 255};

    renderText(renderer,font,"PAUSE",400,200,white);
    renderText(renderer,font,"Press ENTER to quit the game",260,300,white);
}

/**
 * @brief Draws the game over screen of the game.
 * @param renderer the renderer (SDL).
 * @param font the font used for texts.
 */
void Board::drawGameOverScreen(SDL_Renderer* renderer,TTF_Font* font){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Color white = {255, 255, 255, 255};

    renderText(renderer,font,"GAME OVER",350,200,white);
    renderText(renderer,font,"Press ENTER to quit the game",260,300,white);
}

