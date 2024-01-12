#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <vector>
#include <QPushButton>
#include "CircleButton.h"
#include "BridgeLine.h"
#include "BaseLine.h"
#include "Board.h"


class BoardWindow : public QObject
{
	Q_OBJECT

public:
	BoardWindow(QGraphicsScene* scene, int width, int height,  Board& b, Player* currentPlayer);
	BoardWindow(QGraphicsScene* scene, int width, int height, Board& b, Player* currentPlayer, bool loadFromFile);
	void setCurrentPlayer(Player* current);
	void drawLines(QGraphicsScene* scene);
	void drawBaseLines(QGraphicsScene* scene);

public slots:
	//void onButtonClicked();
	void onButtonClicked(int x, int y, CircleButton* button);
	void onSaveGameClicked() 
	{
		emit saveGameRequested();
	}
signals:
	void pointAdded(int x, int y, CircleButton* button);
	void saveGameRequested();
private:
	Board& m_board;
	std::vector<CircleButton*> m_points;
	std::vector<BridgeLine*> m_lines;
	QGraphicsScene* s;
	Player* m_currentPlayer;
	QGraphicsTextItem* m_currentPlayerText;
	QGraphicsTextItem* m_currentPlayerPointsText;
	QGraphicsTextItem* m_currentPlayerBridgesText;
	QPushButton* saveButton;
};

#endif //BOARDWINDOW_H