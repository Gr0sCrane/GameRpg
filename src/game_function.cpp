#include <iostream>
#include "game_function.hpp"
#include "board.hpp"
#include "combat.hpp"

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

void HealPlayerOnItem(std::shared_ptr<Player> player, Board& board, Position pos) {
	Entity* entity = board.getEntityAt(pos).get();
	Heal* healItem = dynamic_cast<Heal*>(entity);
	if (healItem) {
		HealPlayer(player, healItem->getHealAmount());
	}
}

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
		if(dynamic_cast<Heal*>(target)){
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

void CollectItem(std::shared_ptr<Player> player, Board& board,Position pos) {
	Position entity_pos = Position(pos.x,pos.y);
    Entity* entity = board.getEntityAt(entity_pos).get();
    Item* item = dynamic_cast<Item*>(entity);
    if (item) {
        board.setEntity(entity_pos, nullptr); // Remove from board
        player->getInventory().addItem(std::unique_ptr<Item>(item));
    }
}

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

bool isMobAt(Position pos, Board& board){
	if (board.getEntityType(pos) == EntityType::MOB){
		return true;
	}
	return false;
}