#ifndef ARTIFICIALINTELLIGENCE_H
#define ARTIFICIALINTELLIGENCE_H

#include "game.h"

class ArtificialIntelligence {
public:
    ArtificialIntelligence(Game *game);
    Direction getBestMove(const std::vector<std::vector<Tile*>>& board, long score);

private:
    long minimax(const std::vector<std::vector<Tile *> > &board, int depth, bool player);
    long getFitnessFunction(const std::vector<std::vector<Tile *> > &board);

    std::vector<std::vector<Tile*>> cloneBoard(const std::vector<std::vector<Tile *> > &board);
    void deleteBoard(std::vector<std::vector<Tile *> > &board);

    std::vector<std::vector<long>> optimization = {{6, 5, 4, 3}, {5, 4, 3, 2}, {4, 3, 2, 1}, {3, 2, 1, 0}};
    Game* game;
};

#endif // ARTIFICIALINTELLIGENCE_H
