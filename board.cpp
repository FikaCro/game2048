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
    int value = rand() % 100 + 1 >= 75 ? 4 : 2;
    board.at(x).at(y)->setValue(value);

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
    switch (direction) {
    case Up:
        break;
    case Down:
        break;
    case Right:
        break;
    case Left:
        break;
    }
    changeRandomTile();
    update();
}
