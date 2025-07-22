#include <iostream>
#include "algorithm.hpp"

void initEnemyAlgortihm(Board& board){
    auto entities = board.getEntities();
    std::vector<std::pair<Position,std::shared_ptr<Entity>>> enemies;

    for (const auto& [position, entity] : entities){
        if (entity->getType() == EntityType::MOB){
            enemies.push_back({position,entity});
        }
    }
    std::cout << "Number of enemies on board: " << enemies.size() << "\n";
}