#include <iostream>
#include "algorithm.hpp"

/**
 * @brief Calculate the distance between the enemy and the player.
 * @param mob the enemy that use this function.
 * @param player the player.
 * 
 * @return the distance between the enemy and the player.
 */
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

/**
 * @brief Set the algortithm for all the enemies on the board.
 * 
 * If the distance between the player and an enemy is 5 or bellow, the enemy will chase the player.
 * 
 * @param player the player.
 * @param board the game board.
 * @param renderer the renderer (SDL).
 * @param font the font used for texts.
 * @param playerTexture, mobTexturethe the texture of the entity.
 */
void initAlgorithm(std::shared_ptr<Player> player,Board& board,SDL_Renderer* renderer,
    TTF_Font* font,SDL_Texture* playerTexture,SDL_Texture* mobTexture)
{
    auto enemyList = board.getEnemiesInBoard();

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
