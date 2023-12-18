#ifndef CIRCLEBUTTON_H
#define CIRCLEBUTTON_H

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include "Player.h"

class CircleButton : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    CircleButton(int x, int y, int line, int column, int diameter, QGraphicsItem* parent = nullptr, Player* currentPlayer = nullptr);
    void setIsClicked(bool a);
    bool getIsClicked();
    int getX();
    int getY();
    int getLine();
    int getColumn();
    bool isClicked=false;
    void resetColor();
    void updateColor(Point::Color playerColor);
    Point::Color getColor();

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
    int m_line, m_column, m_x, m_y;
};



#endif // CIRCLEBUTTON_H

