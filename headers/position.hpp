#include <iostream>
#include <functional>

/**
 * @struct Position
 * @brief Represent a position on the board.
 * 
 */
struct Position {
    int x;
    int y;

    Position(int x = 0,int y = 0) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

};
namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& pos) const {
            return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
        }
    };
}

/**
 * @enum Direction
 * @brief Enum class that represent a direction
 * for movement.
 * @return a direction used for movement: UP, DOWN, LEFT, RIGHT or NONE.
 */
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};