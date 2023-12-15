#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <vector>
#include "CircleButton.h"
#include "BridgeLine.h"
#include "Board.h"

class BoardWindow : public QObject
{
	Q_OBJECT

public:
	BoardWindow(QGraphicsScene* scene, int width, int height,  Board& b);

	void drawLines(QGraphicsScene* scene);
public slots:
	//void onButtonClicked();
	void onButtonClicked(int x, int y);
signals:
	void pointAdded(int x, int y, CircleButton* button);

private:
	 Board& m_board;
	std::vector<CircleButton*> m_points;
	std::vector<BridgeLine*> m_lines;
	QGraphicsScene* s;
};

#endif //BOARDWINDOW_H