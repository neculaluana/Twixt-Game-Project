#include "BoardWindow.h"


BoardWindow::BoardWindow(QGraphicsScene* scene)
{
	QGraphicsRectItem* board = new QGraphicsRectItem(0, 0, 100, 100);
	board->setBrush(QBrush(Qt::red));
	scene->addItem(board);
	
}