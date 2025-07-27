#include <random>
#include "board.hpp"
#include "mob.hpp"

const Position kDefault_pos = Position(0,0);

const std::string names[] = {"Miku","Teto","Neru","Dante","Rosalina","Borat","GojoTurk","Bunbun"};

Position generateRandomPosition(int boardSize, Board& board);
Position generateRandomItemPosition(int boardSize, Board& board);
std::string generateRandomName();
int playerBasedHp(std::shared_ptr<Player> player);
double playerBasedAttack(std::shared_ptr<Player> player);
double playerBasedDefense(std::shared_ptr<Player> player);
void spawnEnemy(Board& board,std::shared_ptr<Player> player);
void spawnHeal(Board& board,std::shared_ptr<Player> player);