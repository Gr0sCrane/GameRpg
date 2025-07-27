#include <random>
#include "board.hpp"

const Position kDefault_pos = Position(0,0);

Position generateRandomPosition(int boardSize, Board& board);
Position generateRandomItemPosition(int boardSize, Board& board);