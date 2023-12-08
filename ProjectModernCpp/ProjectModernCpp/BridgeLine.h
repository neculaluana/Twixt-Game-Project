#ifndef BRIDGELINE_H
#define BRIDGELINE_H
#include "CircleButton.h"
#include <QGraphicsLineItem>

class BridgeLine : public QGraphicsLineItem
{
public:
    BridgeLine(CircleButton* startButton=nullptr, CircleButton* endButton=nullptr, QGraphicsItem* parent = nullptr);
    void updatePosition();
private:
    CircleButton* startButton;
    CircleButton* endButton;
};

#endif // BRIDGELINE_H
