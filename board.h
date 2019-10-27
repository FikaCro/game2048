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
    void reset();

protected:
    void keyPressEvent(QKeyEvent* keyEvent) Q_DECL_OVERRIDE;

private:
    void changeRandomTile();
    bool isFull();
    void move(Direction direction);
    void updateScore(long score);

    uint dimension;
    std::vector<std::vector<Tile*>> board;
    long score;
    QGraphicsTextItem* score_item;
};

#endif // BOARD_H
