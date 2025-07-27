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

    for (const auto &[position, entity] : entities)
    {
        if (entity->getType() == EntityType::MOB)
        {
            enemies.push_back({position, entity});
        }
    }
    std::cout << "///DEBUG CONSOLE///" << "\n";
    std::cout << "Number of enemies on board: " << enemies.size() << "\n";
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

                /*DEBUG ON CONSOLE*/
                std::cout << "Distance to " << name << " : " << distance << "\n";

                if (distance <= 5){
                    mob->setChase();
                    mob->chase(player,distance,board,renderer,font,playerTexture,mobTexture);
                } else {
                    mob->setPatrol();
                    mob->patrol(board,renderer,font,playerTexture,mobTexture);
                }
            }
        }
    }
}
