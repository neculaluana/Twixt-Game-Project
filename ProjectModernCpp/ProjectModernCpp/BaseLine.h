#ifndef BASELINE_H
#define BASELINE_H
#include "CircleButton.h"
#include <QPainter>
#include <QGraphicsLineItem>

class BaseLine : public QGraphicsLineItem
{
public:
    BaseLine(CircleButton* startButton = nullptr, CircleButton* endButton = nullptr, QColor color = nullptr, QGraphicsItem* parent = nullptr, bool aux=NULL);
    void updatePositionTL();
    void updatePositionRB();

    void updatePen();
private:
    CircleButton* startButton;
    CircleButton* endButton;
    QColor color;
};

#endif // BRIDGELINE_H
