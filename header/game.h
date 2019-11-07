#ifndef GAME_H
#define GAME_H

#include "tile.h"

enum Direction {
    Up = 0,
    Down = 1,
    Right = 2,
    Left = 3,
    Last
};

class Game {
public:
    Game();
    ~Game();

    std::pair<bool, long> move(Direction direction, std::vector<std::vector<Tile*>>& board);
    void changeRandomTile(std::vector<std::vector<Tile*>>& board);
    void reset(std::vector<std::vector<Tile *> > &board);
    bool isFull(const std::vector<std::vector<Tile*> > &board);
    bool canMove(const std::vector<std::vector<Tile*> > &board);
};

#endif // GAME_H
