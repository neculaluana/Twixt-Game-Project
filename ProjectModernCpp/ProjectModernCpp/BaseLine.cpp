#include "BaseLine.h"

BaseLine::BaseLine(CircleButton* startButton, CircleButton* endButton, QColor color, QGraphicsItem* parent, bool aux)
    : QGraphicsLineItem(parent), startButton(startButton), endButton(endButton),color(color)
{
    QPen pen(color, 2);
    setPen(pen);
    if (aux == 0)
        updatePositionTL();
    else
        updatePositionRB();
    updatePen();
}



void BaseLine::updatePositionTL()
{
    if (startButton && endButton) {
        QPointF startPoint = startButton->pos();
        QPointF endPoint = endButton->pos();

        startPoint.setX(startPoint.x() - 10);
        endPoint.setX(endPoint.x() - 10);
        startPoint.setY(startPoint.y() - 10);
        endPoint.setY(endPoint.y() - 10);
        QLineF newLine(startPoint, endPoint);

        setLine(newLine);
    }
    update();
}

void BaseLine::updatePositionRB()
{
    if (startButton && endButton) {
        QPointF startPoint = startButton->pos();
        QPointF endPoint = endButton->pos();

        startPoint.setX(startPoint.x() + 18);
        endPoint.setX(endPoint.x() + 18);
        startPoint.setY(startPoint.y() + 16);
        endPoint.setY(endPoint.y() + 16);
        QLineF newLine(startPoint, endPoint);

        setLine(newLine);
    }
    update();
}
void BaseLine::updatePen()
{
    if (!startButton || !endButton) return;
    QPen pen(color, 2);
    setPen(pen);
}


