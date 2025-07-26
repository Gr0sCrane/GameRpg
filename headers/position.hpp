#include <iostream>
#include <functional>

/**
 * @struct Position
 * @brief Represent a position on the board.
 * @param x X coord
 * @param y Y coord
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

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};