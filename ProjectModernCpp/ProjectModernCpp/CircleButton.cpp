#include "CircleButton.h"
#include <QGraphicsSceneMouseEvent>

CircleButton::CircleButton(int x, int y, int diameter, QGraphicsItem* parent)
    : QGraphicsEllipseItem(parent), isClicked(false) {

    setRect(0, 0, diameter, diameter);
    setPos(x - diameter / 2, y - diameter / 2);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGray);
    setBrush(brush);


    setAcceptHoverEvents(true);
}

void CircleButton::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    emit clicked();
    isClicked = true;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
    update();
}

void CircleButton::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if(!isClicked)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        setBrush(brush);
    }
}

void CircleButton::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    if (!isClicked)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::lightGray);
        setBrush(brush);
    }
}

void CircleButton::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    if(!isClicked)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
       brush.setColor(Qt::darkGray);
        setBrush(brush);
    }
}
