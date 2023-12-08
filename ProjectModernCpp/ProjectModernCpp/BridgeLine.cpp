#include "BridgeLine.h"

BridgeLine::BridgeLine(CircleButton* startButton, CircleButton* endButton, QGraphicsItem* parent = nullptr)
    : QGraphicsLineItem(parent), startButton(startButton), endButton(endButton)
{}