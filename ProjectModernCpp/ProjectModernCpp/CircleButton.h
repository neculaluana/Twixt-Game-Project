#ifndef CIRCLEBUTTON_H
#define CIRCLEBUTTON_H

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QBrush>


class CircleButton : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    CircleButton(int x, int y, int diameter, QGraphicsItem* parent = nullptr);


signals:
    void clicked();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;


};



#endif // CIRCLEBUTTON_H

