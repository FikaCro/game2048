#include "game.h"

Game::Game(uint dimension)
{
    this->dimension = dimension;
    score = 0;
}

Game::~Game()
{
}

void Game::initGame(std::vector<std::vector<Tile *> > &tiles)
{
    for (uint i = 0; i < dimension; i++) {
    }

}

bool Game::isFull()
{
    //return std::find(board.begin(), board.end(), 0) == board.end() ? true : false;
    return false;
}

void Game::move(Direction direction)
{
    uint dimension = 4;
    switch (direction) {
    case Up:
        for (uint i = dimension - 1; i >= 0; i--) {
            for (uint j = 0; j < dimension; j++) {

            }
        }
        break;
    case Down:
        break;
    case Right:
        break;
    case Left:
        break;

    }
}

void Game::restartGame()
{
    score = 0;
}
