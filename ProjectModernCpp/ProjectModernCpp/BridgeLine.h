#ifndef BRIDGELINE_H
#define BRIDGELINE_H
#include "CircleButton.h"
#include <QPainter>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

class BridgeLine :public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    BridgeLine(CircleButton* startButton=nullptr, CircleButton* endButton=nullptr, QColor color = nullptr, QGraphicsItem* parent = nullptr);
    void updatePosition();
    void updatePen();

    CircleButton* getStartButton();
    CircleButton* getEndButton();
    bool getIsClicked();
    QColor getColor();

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

signals:
    void bridgeClicked(BridgeLine* b);
protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
private:
    CircleButton* startButton;
    CircleButton* endButton;
    QColor m_color;
    bool m_isClicked = false;
};

#endif // BRIDGELINE_H
