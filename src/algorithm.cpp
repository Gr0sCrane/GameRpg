#include <iostream>
#include "algorithm.hpp"

int calculateDistance(std::shared_ptr<Mob> mob, std::shared_ptr<Player> player)
{

    Position mobPos = mob->getPosition();
    Position playerPos = player->getPosition();
    int calculX = mobPos.x - playerPos.x;
    int calculY = mobPos.y - playerPos.y;
    int powerX = static_cast<int>(pow(calculX, 2));
    int powerY = static_cast<int>(pow(calculY, 2));
    int calcul = powerX + powerY;
    return sqrt(calcul);
}

std::vector<std::pair<Position, std::shared_ptr<Entity>>> initEnemyAlgortihm(Board &board, std::shared_ptr<Player> player)
{

    auto entities = board.getEntities();
    std::vector<std::pair<Position, std::shared_ptr<Entity>>> enemies;

    if (entities.empty()){
        return {};
    }

    enemies = board.getEnemiesInBoard();
    return enemies;
}

void setAlgorithm(std::shared_ptr<Player> player,Board& board,SDL_Renderer* renderer,
    TTF_Font* font,SDL_Texture* playerTexture,SDL_Texture* mobTexture)
{
    auto enemyList = initEnemyAlgortihm(board,player);

    if(!enemyList.empty()){
        for (size_t i = 0; i < enemyList.size(); i++){

            auto e = enemyList[static_cast<int>(i)];
            std::shared_ptr<Mob> mob = std::dynamic_pointer_cast<Mob>(e.second);
            if (mob) {
                int distance = calculateDistance(mob,player);
                std::string name = mob->getMobName();

                if (distance <= 5){
                    mob->chase(player,board,renderer,font,playerTexture,mobTexture);
                } else {
                    mob->patrol(board,renderer,font,playerTexture,mobTexture);
                }
            }
        }
    }
}
