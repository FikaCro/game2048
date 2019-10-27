#include "tile.h"

#include <QPainter>
#include <QGraphicsScene>

Tile::Tile() : QGraphicsItem()
{
    value = 0;

    width = 0;
    height = 0;
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);

    width = scene()->width()*0.225;
    height = scene()->height()*0.225;
    double radius = 5;

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    switch (value) {
    case 0:
        pen.setColor(QColor("#cdc1b4"));
        brush.setColor(QColor("#cdc1b4"));
        break;
    case 2:
        pen.setColor(QColor("#eee4da"));
        brush.setColor(QColor("#eee4da"));
        break;
    case 4:
        pen.setColor(QColor("#ede0c8"));
        brush.setColor(QColor("#ede0c8"));
        break;
    case 8:
        pen.setColor(QColor("#f2b179"));
        brush.setColor(QColor("#f2b179"));
        break;
    case 16:
        pen.setColor(QColor("#f59563"));
        brush.setColor(QColor("#f59563"));
        break;
    case 32:
        pen.setColor(QColor("#f67c5f"));
        brush.setColor(QColor("#f67c5f"));
        break;
    case 64:
        pen.setColor(QColor("#f65e3b"));
        brush.setColor(QColor("#f65e3b"));
        break;
    case 128:
        pen.setColor(QColor("#edcf72"));
        brush.setColor(QColor("#edcf72"));
        break;
    case 256:
        pen.setColor(QColor("#edcc61"));
        brush.setColor(QColor("#edcc61"));
        break;
    case 512:
        pen.setColor(QColor("#edc850"));
        brush.setColor(QColor("#edc850"));
        break;
    case 1024:
        pen.setColor(QColor("#edc53f"));
        brush.setColor(QColor("#edc53f"));
        break;
    case 2048:
        pen.setColor(QColor("#edc22e"));
        brush.setColor(QColor("#edc22e"));
        break;
    default:
        break;
    }

    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRoundedRect(QRectF(-width/2, -height/2, width, height), radius, radius);

    if (value != 0) {
        QFont font;
        font.setPointSize(32);
        font.setBold(true);
        painter->setFont(font);

        pen.setColor("#776E65");
        painter->setPen(pen);

        painter->scale(1, -1);
        painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(value));
    }
}

QRectF Tile::boundingRect() const
{
    return QRectF(-width/2, -height/2, width, height);
}

int Tile::getValue()
{
    return value;
}

void Tile::setValue(int value)
{
    this->value = value;
}

void Tile::setValueRandom()
{
    value = rand() % 100 + 1 >= 90 ? 4 : 2;
}

void Tile::mergeTiles()
{
    value *= 2;
}

bool Tile::getMergedThisTurn()
{
    return merged_this_turn;
}

void Tile::setMergedThisTurn(bool merged)
{
    merged_this_turn = merged;
}
