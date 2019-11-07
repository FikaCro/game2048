#ifndef SCENE_H
#define SCENE_H

#include "artificialintelligence.h"
#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    Scene(ulong dimension, QObject *parent = nullptr);
    ~Scene() Q_DECL_OVERRIDE;
    void initBoardGame();
    void reset();
    void aiPlay();

protected:
    void keyPressEvent(QKeyEvent* keyEvent) Q_DECL_OVERRIDE;

private:
    void updateScore();

    Game* game;
    ArtificialIntelligence* ai;

    std::vector<std::vector<Tile*>> board;
    ulong dimension;
    long score;
    QGraphicsTextItem* score_item;

signals:
    void gameOver(long score);
};

#endif // SCENE_H
