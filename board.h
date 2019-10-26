#ifndef BOARD_H
#define BOARD_H

#include "tile.h"

#include <QGraphicsScene>

class Board : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Direction {
        Up, Down, Right, Left
    };

    Board(uint dimension, QObject *parent = nullptr);
    ~Board() Q_DECL_OVERRIDE;
    void initBoardGame();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent* keyEvent) Q_DECL_OVERRIDE;

private:
    void reset();
    void changeRandomTile();
    bool isFull();
    void move(Direction direction);

    uint dimension;
    std::vector<std::vector<Tile*>> board;
    long score;
};

#endif // BOARD_H
