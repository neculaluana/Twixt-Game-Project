#ifndef BRIDGELINE_H
#define BRIDGELINE_H
#include "CircleButton.h"
#include <QGraphicsLineItem>

class BridgeLine : public QGraphicsLineItem
{
public:
    BridgeLine(CircleButton* startButton, CircleButton* endButton, QGraphicsItem* parent = nullptr);

private:
    CircleButton* startButton;
    CircleButton* endButton;
};

#endif // BRIDGELINE_H
