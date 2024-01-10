#include "BridgeLine.h"

BridgeLine::BridgeLine(CircleButton* startButton, CircleButton* endButton,QColor color, QGraphicsItem* parent)
    : QGraphicsLineItem(parent), startButton(startButton), endButton(endButton)
{
    QPen pen(color, 2); 
    setPen(pen);
    updatePosition();
    updatePen();
}

void BridgeLine::updatePosition()
{
    if (startButton && endButton) {
        QPointF startPoint = startButton->pos();
        QPointF endPoint = endButton->pos();

        startPoint.setX(startPoint.x() + 4);
        startPoint.setY(startPoint.y() + 4);
        endPoint.setX(endPoint.x() + 4);
        endPoint.setY(endPoint.y() + 4);

        QLineF newLine(startPoint, endPoint);
        setLine(newLine);
    }
    update();
}
void BridgeLine::updatePen()
{
    if (!startButton || !endButton) return;

    QColor color = endButton->getQtColor(); 
    QPen pen(color, 2); 
    setPen(pen);
}

CircleButton* BridgeLine::getStartButton()
{
    return startButton;
}

CircleButton* BridgeLine::getEndButton()
{
    return endButton;
}


QRectF BridgeLine::boundingRect() const 
{
    if (!startButton || !endButton) {
        return QRectF();
    }

    QPointF startPoint = startButton->pos();
    QPointF endPoint = endButton->pos();

    qreal left = std::min(startPoint.x(), endPoint.x());
    qreal right = std::max(startPoint.x(), endPoint.x());
    qreal top = std::min(startPoint.y(), endPoint.y());
    qreal bottom = std::max(startPoint.y(), endPoint.y());

    QRectF rect(left, top, right - left, bottom - top);
    qreal margin = 1.0;
    rect.adjust(-margin, -margin, margin, margin);
    return rect;
}

void BridgeLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) 
{
    if (!startButton || !endButton) return;
    QColor color = endButton->getQtColor();
    QPen pen(color, 2); 
    painter->setPen(pen);

    painter->drawLine(line());
}