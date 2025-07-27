#include <iostream>
#include "entity_spawn.hpp"

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

Position generateRandomItemPosition(int boatdsize, Board& board) {
    std::random_device rd; 
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, boatdsize - 1);
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

std::string generateRandomName(){

    int randint = rand() % 8;
    return names[randint];
}

int playerBasedHp(std::shared_ptr<Player> player){
    int lvl = player->getStats().level;
    if(lvl <= 1){
        return 25;
    } else {
        return lvl * 1.25;
    }
}

double playerBasedAttack(std::shared_ptr<Player> player){
    double attack = player->getStats().attack;
    int lvl = player->getStats().attack;
    if (lvl > 1){
        return attack * 1.25;
    }
    return 2.0;
}

double playerBasedDefense(std::shared_ptr<Player> player){
    double defense = player->getStats().defense;
    int lvl = player->getStats().level;
    if (lvl > 1){
        return defense * 1.25;
    }
    return 2.0;
}



void spawnEnemy(Board& board,std::shared_ptr<Player> player){

    std::string name1 = generateRandomName();
    std::string name2 = generateRandomName();
    std::string name3 = generateRandomName();

    int enemyHp = playerBasedHp(player);
    double enemyAttack = playerBasedAttack(player);
    double enemyDefense = playerBasedDefense(player);

    auto enemy1 = std::make_shared<Mob>(name1,Stats(enemyHp,enemyAttack,enemyDefense),kDefault_pos);
    auto enemy2 = std::make_shared<Mob>(name2,Stats(enemyHp,enemyAttack,enemyDefense),kDefault_pos);
    auto enemy3 = std::make_shared<Mob>(name3,Stats(enemyHp,enemyAttack,enemyDefense),kDefault_pos);

    board.setEntity(generateRandomPosition(kBoardSize, board), std::static_pointer_cast<Entity>(enemy1));
    board.setEntity(generateRandomPosition(kBoardSize, board), std::static_pointer_cast<Entity>(enemy2));
    board.setEntity(generateRandomPosition(kBoardSize, board), std::static_pointer_cast<Entity>(enemy3));

    
}