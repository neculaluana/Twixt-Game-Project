#ifndef BRIDGELINE_H
#define BRIDGELINE_H
#include "CircleButton.h"
#include <QPainter>
#include <QGraphicsLineItem>

class BridgeLine : public QGraphicsLineItem
{
public:
    BridgeLine(CircleButton* startButton=nullptr, CircleButton* endButton=nullptr, QGraphicsItem* parent = nullptr);
    void updatePosition();
protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
private:
    CircleButton* startButton;
    CircleButton* endButton;
};

#endif // BRIDGELINE_H
