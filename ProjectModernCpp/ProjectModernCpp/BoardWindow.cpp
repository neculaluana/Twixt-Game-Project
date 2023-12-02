#include "BoardWindow.h"


BoardWindow::BoardWindow(QGraphicsScene* scene, int width, int height,const Board& b )
{
	QGraphicsRectItem* board = new QGraphicsRectItem(width/20, height/13, 630, 630);
	board->setBrush(QBrush(Qt::lightGray));
	scene->addItem(board);

	//m_points.resize(b.getBoardSize());
	//for()
	
}