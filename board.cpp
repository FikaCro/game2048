#include "board.h"

#include <time.h>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

Board::Board(uint dimension, QObject *parent) : QGraphicsScene(parent)
{
    this->dimension = dimension;
    board.resize(dimension);
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
    //changeRandomTile();
}

void Board::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect)

    QPen pen;
    pen.setColor(Qt::lightGray);
    painter->setPen(pen);

    for (double i = 0; i < width(); i += width()/4) {
        painter->drawLine(QPointF(i, 0), QPointF(i, height()));
    }
    for (double i = 0; i < height(); i += height()/4) {
        painter->drawLine(QPointF(0, i), QPointF(width(), i));
    }
}

void Board::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case Qt::Key_Up:
        move(Direction::Up);
        qDebug() << "up";
        break;
    case Qt::Key_Down:
        move(Direction::Down);
        qDebug() << "down";
        break;
    case Qt::Key_Right:
        move(Direction::Right);
        qDebug() << "right";
        break;
    case Qt::Key_Left:
        move(Direction::Left);
        qDebug() << "left";
        break;
    }
}

void Board::reset()
{
    for (uint i = 0; i < dimension; i++) {
        for (uint j = 0; j < dimension; j++) {
            board.at(i).at(j)->setValue(0);
        }
    }
}

void Board::changeRandomTile()
{
    int x, y;
    srand(time(NULL));
    while (true) {
        x = rand() % 4;
        y = rand() % 4;
        if (board.at(x).at(y)->getValue() == 0) {
            break;
        }
    }
    board.at(x).at(y)->setValueRandom();

    if (isFull()) {
        qDebug() << "IZGUBIO SI";
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
    switch (direction) {
    case Up:
        for(int i = dimension-1; i >=0; i--) {
             for(int j = 0; j < dimension; j++) {
                 if (board.at(i).at(j) != 0) {
                     for (int k = dimension-1; k > j; k--) {
                         if (board.at(i).at(k)->getValue() == 0) {
                             board.at(i).at(k)->setValue(board.at(i).at(j)->getValue());
                             board.at(i).at(j)->setValue(0);
                             move_success = true;
                         }
                         else if (board.at(i).at(k)->getValue() == board.at(i).at(j)->getValue() &&
                                  (board.at(i).at(k-1)->getValue()==0 || board.at(i).at(k-1)->getValue() == board.at(i).at(k)->getValue())) {
                             board.at(i).at(k)->mergeTiles();
                             board.at(i).at(j)->setValue(0);
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
                 if (board.at(i).at(j) != 0) {
                     for (int k = 0; k < j; k++) {
                         if (board.at(i).at(k)->getValue() == 0) {
                             board.at(i).at(k)->setValue(board.at(i).at(j)->getValue());
                             board.at(i).at(j)->setValue(0);
                             move_success = true;
                         }
                         else if (board.at(i).at(k)->getValue() == board.at(i).at(j)->getValue() &&
                                  (board.at(i).at(k+1)->getValue()==0 || board.at(i).at(k+1)->getValue() == board.at(i).at(k)->getValue())) {
                             board.at(i).at(k)->mergeTiles();
                             board.at(i).at(j)->setValue(0);
                             move_success = true;
                         }
                     }
                 }
             }
         }
        break;
    case Right:
        break;
    case Left:
        for(int i = 0; i < dimension; i++) {
             for(int j = 0; j < dimension; j++) {
                 if (board.at(i).at(j) != 0) {
                     for (int k = 0; k < i; k++) {
                         if (board.at(k).at(j)->getValue() == 0) {
                             board.at(k).at(j)->setValue(board.at(i).at(j)->getValue());
                             board.at(i).at(j)->setValue(0);
                             move_success = true;
                         }
                         else if (board.at(k).at(j)->getValue() == board.at(i).at(j)->getValue() &&
                                  (board.at(k+1).at(j)->getValue()==0 || board.at(k+1).at(j)->getValue() == board.at(k).at(j)->getValue())) {
                             board.at(k).at(j)->mergeTiles();
                             board.at(i).at(j)->setValue(0);
                             move_success = true;
                         }
                     }
                 }
             }
         }
        break;
    }
    if (move_success) {
        changeRandomTile();
        update();
    }
}
