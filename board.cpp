#include "board.h"

#include <QPainter>
#include <QKeyEvent>
#include <QTextItem>

Board::Board(uint dimension, QObject *parent) : QGraphicsScene(parent)
{
    this->dimension = dimension;
    board.resize(dimension);

    score = 0;
}

Board::~Board()
{
}

void Board::initBoardGame()
{
    for (uint i = 0; i < dimension; i++) {
        for (uint j = 0; j < dimension; j++) {
            Tile* tile = new Tile();
            tile->setPos(QPointF(i*width()/dimension + width()/dimension/2, j*height()/dimension + height()/dimension/2));
            addItem(tile);
            board.at(i).push_back(tile);
        }
    }
    changeRandomTile();

    score_item = new QGraphicsTextItem();
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    score_item->setFont(font);
    score_item->setDefaultTextColor(QColor("#776E65"));
    addItem(score_item);
    score_item->setPos(50, 630);
    score_item->setTransform(QTransform::fromScale(1, -1));
    updateScore(score);
}

void Board::reset()
{
    for (uint i = 0; i < dimension; i++) {
        for (uint j = 0; j < dimension; j++) {
            board.at(i).at(j)->setValue(0);
        }
    }
    changeRandomTile();
    update();
}

void Board::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case Qt::Key_Up:
        move(Direction::Up);
        break;
    case Qt::Key_Down:
        move(Direction::Down);
        break;
    case Qt::Key_Right:
        move(Direction::Right);
        break;
    case Qt::Key_Left:
        move(Direction::Left);
        break;
    }
}

void Board::changeRandomTile()
{
    uint x, y;
    while (true) {
        x = rand() % dimension;
        y = rand() % dimension;
        if (board.at(x).at(y)->getValue() == 0) {
            break;
        }
    }
    board.at(x).at(y)->setValueRandom();

    if (isFull()) {
        reset();
    }
}

bool Board::isFull()
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

void Board::move(Board::Direction direction)
{
    bool move_success = false;
    std::list<Tile*> merged_tiles;

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

                             updateScore(board.at(i).at(k)->getValue());

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

                             updateScore(board.at(i).at(k)->getValue());

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

                             updateScore(board.at(k).at(j)->getValue());

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

                             updateScore(board.at(k).at(j)->getValue());

                             board.at(k).at(j)->setMergedThisTurn(true);
                             merged_tiles.push_back(board.at(k).at(j));
                             move_success = true;
                         }
                     }
                 }
             }
         }
        break;
    }
    if (move_success) {
        for (auto&& tile : merged_tiles) {
            tile->setMergedThisTurn(false);
        }

        changeRandomTile();
        update();
    }
}

void Board::updateScore(long score)
{
    this->score += score;
    score_item->setPlainText(QString("Score: %1").arg(this->score));
    update();
}
