#ifndef BASELINE_H
#define BASELINE_H
#include "CircleButton.h"
#include <QPainter>
#include <QGraphicsLineItem>

class BaseLine : public QGraphicsLineItem
{
public:
    BaseLine(CircleButton* startButton = nullptr, CircleButton* endButton = nullptr, QColor color = nullptr, QGraphicsItem* parent = nullptr);
    void updatePosition();
    void updatePen();
protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
private:
    CircleButton* startButton;
    CircleButton* endButton;
};

#endif // BRIDGELINE_H
