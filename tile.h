#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QGraphicsItem>

class Tile : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Tile();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) Q_DECL_OVERRIDE;
    QRectF boundingRect() const Q_DECL_OVERRIDE;

    int getValue();
    void setValue(int value);
    void setValueRandom();
    void mergeTiles();
    bool getMergedThisTurn();
    void setMergedThisTurn(bool merged);

private:
    int value;
    bool merged_this_turn;
};

#endif // TILE_H
