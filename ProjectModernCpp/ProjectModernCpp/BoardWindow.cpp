#include "BoardWindow.h"


BoardWindow::BoardWindow(QGraphicsScene* scene, int width, int height,const Board& b )
{
	QGraphicsRectItem* board = new QGraphicsRectItem(width/20, height/13, 630, 630);
	board->setBrush(QBrush(Qt::lightGray));
	scene->addItem(board);

	//m_points.resize(b.getBoardSize());
	//for()

    size_t boardSize = b.getBoardSize();
    m_points.resize(boardSize);


    int cellWidth = 630 / boardSize;
    int cellHeight = 630 / boardSize;

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            int x = width / 20 + i * cellWidth + cellWidth / 2;
            int y = height / 13 + j * cellHeight + cellHeight / 2;

            QGraphicsEllipseItem* point = new QGraphicsEllipseItem(x - 2, y - 2, 4, 4);
            point->setBrush(QBrush(Qt::darkGray));
            scene->addItem(point);
        }
    }
	
}