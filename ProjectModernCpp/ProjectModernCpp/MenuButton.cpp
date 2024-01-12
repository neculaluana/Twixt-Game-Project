#include"MenuButton.h"

#include <QGraphicsTextItem>
#include <QBrush>

MenuButton::MenuButton(QString name, QGraphicsItem* parent) : QGraphicsRectItem(parent) {
    
    enableButton = true;
    setRect(0, 0, 200, 50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
    text = new QGraphicsTextItem(name, this);
    int xPos = rect().width() / 2 - text->boundingRect().width() / 2;
    int yPos = rect().height() / 2 - text->boundingRect().height() / 2;
    text->setPos(xPos, yPos);
    setAcceptHoverEvents(true);
}

void MenuButton::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if(enableButton)
    emit clicked();
}

void MenuButton::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
}

void MenuButton::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}