#include "header/game.h"

Game::Game()
{
}

Game::~Game()
{
}

std::pair<bool, long> Game::move(Direction direction, std::vector<std::vector<Tile *> > &board)
{
    bool move_success = false;
    long score = 0;

    std::list<Tile*> merged_tiles;
    int dimension = board.size();

    switch (direction) {
    case Up:
        for(int i = 0; i < dimension; i++) {
             for(int j = dimension - 1; j >= 0; j--) {
                 if (board.at(i).at(j)->getValue() != 0) {
                     for (int k = dimension-1; k > j; k--) {
                         if (board.at(i).at(k)->getValue() == 0) {
                             board.at(i).at(k)->setValue(board.at(i).at(j)->getValue());
                             board.at(i).at(j)->setValue(0);
                             move_success = true;
                         }
                         else if (board.at(i).at(k)->getValue() == board.at(i).at(j)->getValue() &&
                                  (board.at(i).at(k-1)->getValue()==0 || board.at(i).at(k-1)->getValue() == board.at(i).at(k)->getValue()) &&
                                  !board.at(i).at(k)->getMergedThisTurn()) {
                             board.at(i).at(k)->mergeTiles();
                             board.at(i).at(j)->setValue(0);

                             score += board.at(i).at(k)->getValue();

                             board.at(i).at(k)->setMergedThisTurn(true);
                             merged_tiles.push_back(board.at(i).at(k));
                             move_success = true;
                         }
                     }
                 }
             }
         }
        break;
    case Down:
        for(int i = 0; i < dimension; i++) {
             for(int j = 0; j < dimension; j++) {
                 if (board.at(i).at(j)->getValue() != 0) {
                     for (int k = 0; k < j; k++) {
                         if (board.at(i).at(k)->getValue() == 0) {
                             board.at(i).at(k)->setValue(board.at(i).at(j)->getValue());
                             board.at(i).at(j)->setValue(0);
                             move_success = true;
                         }
                         else if (board.at(i).at(k)->getValue() == board.at(i).at(j)->getValue() &&
                                  (board.at(i).at(k+1)->getValue()==0 || board.at(i).at(k+1)->getValue() == board.at(i).at(k)->getValue()) &&
                                  !board.at(i).at(k)->getMergedThisTurn()) {
                             board.at(i).at(k)->mergeTiles();
                             board.at(i).at(j)->setValue(0);

                             score += board.at(i).at(k)->getValue();

                             board.at(i).at(k)->setMergedThisTurn(true);
                             merged_tiles.push_back(board.at(i).at(k));
                             move_success = true;
                         }
                     }
                 }
             }
         }
        break;
    case Right:
        for(int i = dimension - 1; i >= 0; i--) {
             for(int j = 0; j < dimension; j++) {
                 if (board.at(i).at(j)->getValue() != 0) {
                     for (int k = dimension-1; k > i; k--) {
                         if (board.at(k).at(j)->getValue() == 0) {
                             board.at(k).at(j)->setValue(board.at(i).at(j)->getValue());
                             board.at(i).at(j)->setValue(0);
                             move_success = true;
                         }
                         else if (board.at(k).at(j)->getValue() == board.at(i).at(j)->getValue() &&
                                  (board.at(k-1).at(j)->getValue()==0 || board.at(k-1).at(j)->getValue() == board.at(k).at(j)->getValue()) &&
                                  !board.at(k).at(j)->getMergedThisTurn()) {
                             board.at(k).at(j)->mergeTiles();
                             board.at(i).at(j)->setValue(0);

                             score += board.at(k).at(j)->getValue();

                             board.at(k).at(j)->setMergedThisTurn(true);
                             merged_tiles.push_back(board.at(k).at(j));
                             move_success = true;
                         }
                     }
                 }
             }
         }
        break;
    case Left:
        for(int i = 0; i < dimension; i++) {
             for(int j = 0; j < dimension; j++) {
                 if (board.at(i).at(j)->getValue() != 0) {
                     for (int k = 0; k < i; k++) {
                         if (board.at(k).at(j)->getValue() == 0) {
                             board.at(k).at(j)->setValue(board.at(i).at(j)->getValue());
                             board.at(i).at(j)->setValue(0);
                             move_success = true;
                         }
                         else if (board.at(k).at(j)->getValue() == board.at(i).at(j)->getValue() &&
                                  (board.at(k+1).at(j)->getValue()==0 || board.at(k+1).at(j)->getValue() == board.at(k).at(j)->getValue()) &&
                                  !board.at(k).at(j)->getMergedThisTurn()) {
                             board.at(k).at(j)->mergeTiles();
                             board.at(i).at(j)->setValue(0);

                             score += board.at(k).at(j)->getValue();

                             board.at(k).at(j)->setMergedThisTurn(true);
                             merged_tiles.push_back(board.at(k).at(j));
                             move_success = true;
                         }
                     }
                 }
             }
         }
        break;
    default:
        break;
    }
    if (move_success) {
        for (auto&& tile : merged_tiles) {
            tile->setMergedThisTurn(false);
        }
    }
    return  std::make_pair(move_success, score);
}

void Game::changeRandomTile(std::vector<std::vector<Tile *> > &board)
{
    ulong dimension = board.size();
    ulong x, y;
    while (true) {
        x = rand() % dimension;
        y = rand() % dimension;
        if (board.at(x).at(y)->getValue() == 0) {
            break;
        }
    }
    board.at(x).at(y)->setValueRandom();
}

void Game::reset(std::vector<std::vector<Tile *> > &board)
{
    ulong dimension = board.size();
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            board.at(i).at(j)->setValue(0);
        }
    }
}

bool Game::isFull(const std::vector<std::vector<Tile *> > &board)
{
    for (auto& vector : board) {
        for (auto& tile : vector) {
            if (tile->getValue() == 0) {
                return false;
            }
        }
    }
    return true;
}

bool Game::canMove(const std::vector<std::vector<Tile *> > &board)
{
    ulong dimension = board.size();
    for (int i = 0; i < dimension - 1; i++) {
        for (int j = 0; j < dimension; j++) {
            if (board.at(i).at(j)->getValue() == board.at(i+1).at(j)->getValue()) {
                return true;
            }
        }
    }
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension - 1; j++) {
            if (board.at(i).at(j)->getValue() == board.at(i).at(j+1)->getValue()) {
                return true;
            }
        }
    }
    return false;
}
