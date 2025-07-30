#include <iostream>
#include "entity_spawn.hpp"

/**
 * @brief Return a position randomly generated with an algorithm.
 * 
 * If the position returned is a player, the function recalculate the position to return another.
 * 
 * @param boardsize the size of the board used in the algorithm.
 * @param board the game board used for the player position condition.
 * @return the generated position.
 */
Position generateRandomPosition(int boardSize, Board& board) { //this is more optimized than the previous version
    std::random_device rd; 
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, boardSize - 1);

    int x = distr(eng);
    int y = distr(eng);

    if (board.getEntityType(Position(x,y)) == EntityType::PLAYER) {
        // Use a loop instead of recursion to avoid ambiguity and stack overflow
        do {
            x = distr(eng);
            y = distr(eng);
        } while (board.getEntityType(Position(x,y)) == EntityType::PLAYER);
    }
    return Position(x,y);
}

/**
 * @brief Return a randomly generated position for an Item.
 * @note this function will be propably get deleted because it looks the same as the 
 * generateRandomPosition() function.
 * 
 * @param boardsize the board size used for thr algorithm.
 * @param board the game board used for the position check.
 * @return the generated position.
 */
Position generateRandomItemPosition(int boardsize, Board& board) {
    std::random_device rd; 
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, boardsize - 1);
    int x = distr(eng);
    int y = distr(eng);
    if (board.getEntityType(Position(x,y)) != EntityType::VOID) {
        do {
            x = distr(eng);
            y = distr(eng);
        } while (board.getEntityType(Position(x,y)) != EntityType::VOID);
    }
    
    return Position(x,y);
}

/**
 * @brief Generate a random name choiced in an array of default names.
 * @return the choiced name.
 */
std::string generateRandomName(){

    int randint = rand() % 8;
    return names[randint];
}

/**
 * @brief Calculate the hp of the generated enemy to be scaled on the player level.
 * @param player the player use for the level.
 * @return the scaled base health points.
 */
int playerBasedHp(std::shared_ptr<Player> player) {
    int baseHp = 10;
    int lvl = player->getStats().level;
    return baseHp + static_cast<int>((lvl - 1) * 5 * 1.25);
}

/**
 * @brief Calculate the attack of the generated enemy to be scaled on the player level.
 * @param player the player use for the level.
 * @return the scaled base attack points.
 */
double playerBasedAttack(std::shared_ptr<Player> player){
    double attack = player->getStats().attack;
    int lvl = player->getStats().attack;
    if (lvl > 1){
        return attack * 0.55;
    }
    return 2.0;
}

/**
 * @brief Calculate the defense of the generated enemy to be scaled on the player level.
 * @param player the player use for the level.
 * @return the scaled base defense.
 */
double playerBasedDefense(std::shared_ptr<Player> player){
    double defense = player->getStats().defense;
    int lvl = player->getStats().level;
    if (lvl > 1){
        return defense * 1.25;
    }
    return 2.0;
}

/**
 * @brief Calculate the hp amount of the generated Heal item to be scaled on the player level.
 * @param player the player use for the level.
 * @return the scaled base health points amount.
 */
double playerBasedHealAmmount(std::shared_ptr<Player> player){
    
    int hp = player->getStats().maxHp;
    return hp / 1.5;
}

/**
 * @brief Generate the enemies and set their positions on the board.
 * 
 * The names and position are both chosen randomly.
 * 
 * @param board the game board.
 * @param player the player used to have the hp, attack and hp amounts of entities to be scaled to the player level.
 */
void spawnEnemy(Board& board,std::shared_ptr<Player> player){

    std::string name1 = generateRandomName();
    std::string name2 = generateRandomName();
    std::string name3 = generateRandomName();

    int enemyHp = playerBasedHp(player);
    double enemyAttack = playerBasedAttack(player);
    double enemyDefense = playerBasedDefense(player);

    auto enemy1 = std::make_shared<Mob>(name1,Stats(enemyHp,enemyAttack,enemyDefense),kDefault_pos);
    auto enemy2 = std::make_shared<Mob>(name2,Stats(enemyHp,enemyAttack,enemyDefense),kDefault_pos);
    auto enemy3 = std::make_shared<Mob>(name3,Stats(enemyHp,enemyAttack,enemyDefense),kDefault_pos);;



    board.setEntity(generateRandomPosition(kBoardSize, board), std::static_pointer_cast<Entity>(enemy1));
    board.setEntity(generateRandomPosition(kBoardSize, board), std::static_pointer_cast<Entity>(enemy2));
    board.setEntity(generateRandomPosition(kBoardSize, board), std::static_pointer_cast<Entity>(enemy3));

}

/**
 * @brief Determine if a heal item can spawn or not on the board based on the player's hp stats.
 * 
 * If there is more than one heal item on the board, the function don't execute.
 * 
 * @param board the game board used to know if there is more than one heal item.
 * @param player the player used to get stats and to know if the function can spawn a heal item or not.
 */
void spawnHeal(Board& board,std::shared_ptr<Player> player){

    if(board.getHealInBoard().empty()){
        int playerHp = player->getStats().hp;
        int playerMaxHp = player->getStats().maxHp;
    
        if (playerHp <= playerMaxHp/2){
            double amount = playerBasedHealAmmount(player);
            auto potionHeal = std::make_shared<Heal>("Heal", amount, kDefault_pos);
            board.setEntity(generateRandomItemPosition(kBoardSize,board),potionHeal);
        }
    }
}