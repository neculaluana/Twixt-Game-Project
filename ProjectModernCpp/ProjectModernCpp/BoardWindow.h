#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <vector>
#include "CircleButton.h"
#include "BridgeLine.h"
#include "BaseLine.h"
#include "Board.h"

class BoardWindow : public QObject
{
	Q_OBJECT

public:
	BoardWindow(QGraphicsScene* scene, int width, int height,  Board& b, Player* currentPlayer);

	void setCurrentPlayer(Player* current);
	//CircleButton* findPoint(const Point& bridgePoint);
	bool isBridgesIntersection(CircleButton* existingBridgeStart, CircleButton* existingBridgeEnd, CircleButton* futurePoint1, CircleButton* futurePoint2);
	void drawLines(QGraphicsScene* scene);
	CircleButton* findPointButton(const Point& point);

	bool isBridgeAlreadyDrawn(CircleButton* startPoint, CircleButton* endPoint);
	void drawBaseLines(QGraphicsScene* scene);

public slots:
	//void onButtonClicked();
	void onButtonClicked(int x, int y, CircleButton* button);

signals:
	void pointAdded(int x, int y, CircleButton* button);

private:
	Board& m_board;
	std::vector<CircleButton*> m_points;
	std::vector<BridgeLine*> m_lines;
	QGraphicsScene* s;
	Player* m_currentPlayer;
};

#endif //BOARDWINDOW_H