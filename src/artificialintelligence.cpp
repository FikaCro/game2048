#include "header/artificialintelligence.h"

#define DEPTH 4

ArtificialIntelligence::ArtificialIntelligence(Game *game)
{
    this->game = game;
}

Direction ArtificialIntelligence::getBestMove(const std::vector<std::vector<Tile *> > &board, long score)
{
    long highest_score = -std::numeric_limits<long>::max();
    Direction best_move = Direction::Last;

    for (int enum_it = Direction::Up; enum_it != Direction::Last; enum_it++) {
        std::vector<std::vector<Tile*>> new_board = cloneBoard(board);

        if (!game->move(static_cast<Direction>(enum_it), new_board).first) {
            deleteBoard(new_board);
            continue;
        }

        long score = minimax(new_board, DEPTH, false);
        deleteBoard(new_board);

        if (score > highest_score) {
            best_move = static_cast<Direction>(enum_it);
            highest_score = score;
        }

    }
    return best_move;
}

long ArtificialIntelligence::minimax(const std::vector<std::vector<Tile *> > &board, int depth, bool player)
{
    if (depth == 0) {
        return getFitnessFunction(board);
    }
    else if (player) {
        long score = -std::numeric_limits<long>::max();
        for (int enum_it = Direction::Up; enum_it != Direction::Last; enum_it++) {
            std::vector<std::vector<Tile*>> new_board = cloneBoard(board);
            auto next = game->move(static_cast<Direction>(enum_it), new_board);

            if (!next.first) {
                deleteBoard(new_board);
                continue;
            }

            long new_score = minimax(new_board, depth-1, false);
            deleteBoard(new_board);

            if (new_score > score) {
                score = new_score;
            }
        }
        return score;
    }
    else {
        long score = 0;
        long size = 0;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                if (board.at(i).at(j)->getValue() != 0) {
                    continue;
                }
                size += 1;
                std::vector<std::vector<Tile*>> new_board = cloneBoard(board);
                new_board.at(i).at(j)->setValue(4);
                long new_score = minimax(new_board, depth-1, true);
                if (new_score != -std::numeric_limits<long>::max()) {
                    score += (new_score / 10);
                }
                deleteBoard(new_board);
                new_board = cloneBoard(board);
                new_board.at(i).at(j)->setValue(2);
                new_score = minimax(new_board, depth-1, true);
                if (new_score != -std::numeric_limits<long>::max()) {
                    score += (new_score * 9 / 10);
                }
                deleteBoard(new_board);
            }
        }
        if (size == 0) {
            return -std::numeric_limits<long>::max();
        }
        return score / size;
    }
}

long ArtificialIntelligence::getFitnessFunction(const std::vector<std::vector<Tile *> > &board)
{
    long score = 0;
    long penalty = 0;

    int dimension = board.size();
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            score += optimization.at(i).at(j) * board.at(i).at(j)->getValue() * board.at(i).at(j)->getValue();

            if (i-1 >= 0) {
                penalty += std::abs(board.at(i).at(j)->getValue() - board.at(i-1).at(j)->getValue());
            }
            if (i+1 < dimension) {
                penalty += std::abs(board.at(i).at(j)->getValue() - board.at(i+1).at(j)->getValue());
            }
            if (j-1 >= 0) {
                penalty += std::abs(board.at(i).at(j)->getValue() - board.at(i).at(j-1)->getValue());
            }
            if (j+1 < dimension) {
                penalty += std::abs(board.at(i).at(j)->getValue() - board.at(i).at(j+1)->getValue());
            }
        }
    }
    return score - penalty;
}

std::vector<std::vector<Tile*>> ArtificialIntelligence::cloneBoard(const std::vector<std::vector<Tile *> > &board)
{
    int dimension = board.size();
    std::vector<std::vector<Tile*>> new_board;
    new_board.resize(dimension);
    for (uint i = 0; i < dimension; i++) {
        for (uint j = 0; j < dimension; j++) {
            new_board.at(i).push_back(new Tile(*board.at(i).at(j)));
        }
    }
    return new_board;
}

void ArtificialIntelligence::deleteBoard(std::vector<std::vector<Tile *> > &board)
{
    for (uint i = 0; i < board.size(); i++) {
        for (uint j = 0; j < board.size(); j++) {
            delete(board.at(i).at(j));
        }
        board.at(i).clear();
    }
    board.clear();
}
