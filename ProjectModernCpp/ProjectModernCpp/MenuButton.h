#pragma once
#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class MenuButton :public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    MenuButton(QString name, QGraphicsItem* parent = NULL);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    bool enableButton;
signals:
    void clicked();

private:
    QGraphicsTextItem* text;
    
};

#endif // MENUBUTTON_H

