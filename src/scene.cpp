#include "header/scene.h"

#include <QPainter>
#include <QKeyEvent>
#include <QTextItem>
#include <QApplication>

Scene::Scene(ulong dimension, QObject *parent) : QGraphicsScene(parent), dimension(dimension)
{
    game = new Game();
    ai = new ArtificialIntelligence(game);

    board.resize(dimension);
    score = 0;
}

Scene::~Scene()
{
    delete(game);
    delete(ai);
}

void Scene::initBoardGame()
{
    for (ulong i = 0; i < dimension; i++) {
        for (ulong j = 0; j < dimension; j++) {
            Tile* tile = new Tile();
            tile->setPos(QPointF(i*width()/dimension + width()/dimension/2, j*height()/dimension + height()/dimension/2));
            addItem(tile);
            board.at(i).push_back(tile);
        }
    }

    score_item = new QGraphicsTextItem();
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    score_item->setFont(font);
    score_item->setDefaultTextColor(QColor("#776E65"));
    addItem(score_item);
    score_item->setPos(50, 630);
    score_item->setTransform(QTransform::fromScale(1, -1));
    updateScore();

    game->changeRandomTile(board);
    update();
}

void Scene::reset()
{
    game->reset(board);
    score = 0;
    game->changeRandomTile(board);
    updateScore();
    update();
}

void Scene::keyPressEvent(QKeyEvent *keyEvent)
{
    std::pair<bool, long> played_score;
    switch (keyEvent->key()) {
    case Qt::Key_Up:
        played_score = game->move(Direction::Up, board);
        break;
    case Qt::Key_Down:
        played_score = game->move(Direction::Down, board);
        break;
    case Qt::Key_Right:
        played_score = game->move(Direction::Right, board);
        break;
    case Qt::Key_Left:
        played_score = game->move(Direction::Left, board);
        break;
    default:
        break;
    }
    if (played_score.first) {
        score += played_score.second;
        updateScore();
        game->changeRandomTile(board);
        update();
        if (game->isFull(board) && !game->canMove(board)) {
            emit gameOver(score);
        }
    }
}


void Scene::aiPlay()
{
    while (true) {
        if(game->isFull(board) && !game->canMove(board)) {
            break;
        }

        Direction best = ai->getBestMove(board, score);

        std::pair<bool, long> played_score;
        if (best == Direction::Last) {
            for (int enum_it = Direction::Up; enum_it != Direction::Last; enum_it++) {
                played_score = game->move(static_cast<Direction>(enum_it), board);
                if (played_score.first) {
                    break;
                }
            }
        }
        else {
            played_score = game->move(best, board);
        }

        if (played_score.first) {
            score += played_score.second;
            updateScore();
            game->changeRandomTile(board);
            QApplication::processEvents();
            update();
        }
        if (!played_score.first)
            break;
    }
    emit gameOver(score);
}

void Scene::updateScore()
{
    score_item->setPlainText(QString("Score: %1").arg(score));
}
