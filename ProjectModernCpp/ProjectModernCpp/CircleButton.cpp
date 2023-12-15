﻿#include "CircleButton.h"
#include <QGraphicsSceneMouseEvent>

CircleButton::CircleButton(int x, int y, int diameter, QGraphicsItem* parent, Player*currentPlayer)
    : QGraphicsEllipseItem(parent), isClicked(false), m_currentPlayer{currentPlayer} {

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
    brush.setColor(color);
    setBrush(brush);
    update();
}

void CircleButton::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
   
    if(!isClicked)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(color);
        setBrush(brush);
    }
    update();
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

void CircleButton::setIsClicked(bool a)
{
    isClicked = a;
}

bool CircleButton::getIsClicked()
{
    return isClicked;
}

void CircleButton::resetColor()
{
    isClicked = false;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    color = Qt::darkGray;
    brush.setColor(color); 
    setBrush(brush);
    update();
}

void CircleButton::updateColor(Point::Color playerColor) {
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    color = playerColor == Point::Color::Red ? Qt::red : Qt::black;
    brush.setColor(color);
    setBrush(brush);
    update();
}

Point::Color CircleButton::getColor()
{
    if (color == Qt::red)
        return Point::Color::Red;
    else
        return Point::Color::Black;
}
