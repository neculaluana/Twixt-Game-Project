#ifndef CIRCLEBUTTON_H
#define CIRCLEBUTTON_H

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include "Player.h"

class CircleButton : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    CircleButton(int x, int y, int diameter, QGraphicsItem* parent = nullptr, Player* currentPlayer = nullptr);
    void setIsClicked(bool a);
    bool getIsClicked();
    bool isClicked=false;
    void resetColor();

signals:
    void clicked();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:

    QColor color;
    Player* m_currentPlayer;
};



#endif // CIRCLEBUTTON_H

