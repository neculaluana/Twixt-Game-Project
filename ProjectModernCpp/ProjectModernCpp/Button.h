#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Button :public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Button(QString name, QGraphicsItem* parent = NULL);

private:
    QGraphicsTextItem* text;
};

#endif // BUTTON_H

