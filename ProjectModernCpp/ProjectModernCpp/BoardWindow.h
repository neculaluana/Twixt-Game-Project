#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <vector>
#include "Board.h"
class BoardWindow
{
public:
	BoardWindow(QGraphicsScene* scene, int width, int height,const Board& b);



private:
	std::vector<QGraphicsEllipseItem*> m_points;

};

#endif //BOARDWINDOW_H