#include "BridgeLine.h"

BridgeLine::BridgeLine(CircleButton* startButton, CircleButton* endButton, QGraphicsItem* parent)
    : QGraphicsLineItem(parent), startButton(startButton), endButton(endButton)
{
    updatePosition();
}



void BridgeLine::updatePosition()
{
    if (startButton && endButton) {
        setLine(QLineF(startButton->pos(), endButton->pos()));
    }
    update();
}

QRectF BridgeLine::boundingRect() const 
{
    if (!startButton || !endButton) {
        return QRectF();
    }

    qreal left = std::min(startButton->pos().x(), endButton->pos().x());
    qreal top = std::min(startButton->pos().y(), endButton->pos().y());
    qreal right = std::max(startButton->pos().x(), endButton->pos().x());
    qreal bottom = std::max(startButton->pos().y(), endButton->pos().y());

    return QRectF(QPointF(left, top), QPointF(right, bottom));
}

void BridgeLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) 
{
    painter->drawLine(line());
    update();
}