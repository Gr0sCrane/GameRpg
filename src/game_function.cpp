#include <iostream>
#include "game_function.hpp"
#include "board.hpp"
#include "combat.hpp"

/**
 * @brief This function return the next position using the direction.
 * 
 * If the movement is out of bounds, the entity get teleported to the opposite side of the board.
 * 
 * If the direction is RIGHT: the y coord is increased by 1.
 * 
 * If the direction is LEFT: the y coord is deincreased by 1.
 * 
 * If the direction is UP: the x coord is deincreased by 1.
 * 
 * If the direction is DOWN: the x coord is increased by 1.
 * 
 * @param posX the X coord.
 * @param posY the Y coord.
 * @param dir the direction gived for the movement.
 * @return the new position of the entity.
 */
Position getDirection(int posX, int posY, Direction dir){
	switch (dir)
	{
	case Direction::RIGHT:
		posY += 1;
		if (posY >= kBoardSize) posY = 0;
		break;
	case Direction::LEFT:
		posY -= 1;
		if (posY < 0) posY = kBoardSize -1;
		break;
	case Direction::UP:
		posX -= 1;
		if (posX < 0) {
			posX = kBoardSize - 1;
		}
		break;
	case Direction::DOWN:
		posX += 1;
		if (posX >= kBoardSize) {
        	posX = 0;
    	}
	default:
		break;
	}
	return Position(posX,posY);
}

/**
 * @brief Heals the player with the amount given. 
 * 
 * If the player's max Health point stats is reached, the function does nothing.
 * @param player the targeted player.
 * @param amount the amount of health point the player get.
 */
void HealPlayer(std::shared_ptr<Player> player, int amount) {
	if (amount < 0) {
		return;
	}
	player->getStats().hp += amount;
	if (player->getStats().hp >= player->getStats().maxHp){
		std::cout << "Error: Can't heal anymore, you reached the maxHp" << std::endl;
		player->getStats().hp = player->getStats().maxHp;
	}
}

/**
 * @brief Heal the player using the Heal item stats.
 * @see HealPlayer().
 * 
 * @param player the player targeted.
 * @param board the game board.
 * @param pos the position of the heal item.
 */
void HealPlayerOnItem(std::shared_ptr<Player> player, Board& board, Position pos) {
	Entity* entity = board.getEntityAt(pos).get();
	Heal* healItem = dynamic_cast<Heal*>(entity);
	if (healItem) {
		HealPlayer(player, healItem->getHealAmount());
	}
}

/**
 * @brief Function that control the movement of an entity.
 * 
 * If the entity is a player, a new position is given, the old position is set as nullptr and the entity is on the
 * new position.
 * 
 * If the player touch a enemy, a fight begin.
 * 
 * If the player touch a Heal item, it heals him.
 * 
 * If the entity is a enemy, the enemy look at first if the new position is walkable, if yes the enemy move,
 * if no the enemy dont move. If the enemy touch a player, it starts a fight.
 * 
 * @param entity the entity targeted
 * @param direction the direction gived to move in the direction in param.
 * @param board the game board.
 * @param renderer the renderer (SDL).
 * @param font the font used for texts.
 * @param playerTexture the player texture.
 * @param mobTexture the mob texture.
 */
void MoveDirection(std::shared_ptr<Entity> entity,
				    Direction direction,
					Board& board,
					SDL_Renderer* renderer,
					TTF_Font* font,
					SDL_Texture* playerTexture,
					SDL_Texture* mobTexture){

	auto pos = entity->getPosition();

	Position targetPos = getDirection(pos.x,pos.y,direction);

	Entity* target = board.getEntityAt(targetPos).get();

	if (entity->getType() == EntityType::PLAYER){
		auto player = std::dynamic_pointer_cast<Player>(entity);
		if (!player){
			return;
		}
		if (dynamic_cast<Heal*>(target)){
			HealPlayerOnItem(player,board,targetPos);
		} else if (board.getEntityType(targetPos) == EntityType::ITEM) {
			CollectItem(player,board,targetPos);
		} else if (isMobAt(targetPos,board)){
			auto mob = std::dynamic_pointer_cast<Mob>(board.getEntityAt(targetPos));
			StartFight(board,player,mob,renderer,font,playerTexture,mobTexture);
		}
	}

	if (entity->getType() == EntityType::MOB){
		if (!board.isWalkable(targetPos)){
			return;
		}
		if (board.getEntityType(targetPos) == EntityType::PLAYER) {
            auto player = std::dynamic_pointer_cast<Player>(board.getEntityAt(targetPos));
            auto mob = std::dynamic_pointer_cast<Mob>(entity);
            StartFight(board, player, mob, renderer, font, playerTexture, mobTexture);
			board.setEntity(pos,nullptr);
			return;
        }
	}

	board.setEntity(targetPos,entity);
	board.setEntity(pos,nullptr);
	entity->setPosition(targetPos);

}

/**
 * @brief This function collect the item at the position given.
 * 
 * @param player the player.
 * @param board the game board.
 * @param pos the position of the item.
 */
void CollectItem(std::shared_ptr<Player> player, Board& board, Position pos) {
    
    auto entityPtr = board.getEntityAt(pos);
    if (!entityPtr) {
        std::cerr << "No entity in this position" << std::endl;
        return;
    }
    auto itemPtr = std::dynamic_pointer_cast<Item>(entityPtr);
    if (!itemPtr) {
        std::cerr << "Entity is not an Item" << std::endl;
        return;
    }
    bool added = player->getInventory().addItem(itemPtr);
    if (!added) {
        std::cerr << "Inventory full" << std::endl;
        return;
    }
    board.setEntity(pos, nullptr);
    
    std::cout << "Item " << itemPtr->getName() << " collected" << std::endl;
}

/**
 * @brief Indicate if the player is near an enemy.
 * @param player the player.
 * @param board the game board.
 * @return true if a enemy is near the player, false if not
 */
bool IsPlayerNearMob(Player* player, Board& board) {
	auto playerPos = player->getPosition();
	for (int x = playerPos.x - 2; x <= playerPos.x + 2; ++x) {
		for (int y = playerPos.y - 2; y <= playerPos.y + 2; ++y) {
			if (x >= 0 && x < kBoardSize && y >= 0 && y < kBoardSize) {
				Entity* entity = board.getEntityAt(Position(x,y)).get();
				if (entity && entity->getType() == EntityType::MOB) {
					return true;
				}
			}
		}
	}
	return false;
}

/**
 * @brief Function that can give the nearest mob.
 * @param player the player.
 * @param board the game board.
 * @return the nearest enemy.
 */
Mob* getNearMob(Player* player, Board& board) {
	auto playerPos = player->getPosition();
	for (int x = playerPos.x - 2; x <= playerPos.x + 2; ++x) {
		for (int y = playerPos.y - 2; y <= playerPos.y + 2; ++y) {
			if (x >= 0 && x < kBoardSize && y >= 0 && y < kBoardSize) {
				Entity* entity = board.getEntityAt(Position(x,y)).get();
				if (entity && entity->getType() == EntityType::MOB) {
					return dynamic_cast<Mob*>(entity);
				}
			}
		}
	}
	return nullptr;
}

/**
 * @brief Gives a boolean result if a enemy is at the given position.
 * @param pos the position on the board
 * @param board the game board
 * @return True if an enemy is at the position, false if not.
 */
bool isMobAt(Position pos, Board& board){
	if (board.getEntityType(pos) == EntityType::MOB){
		return true;
	}
	return false;
}