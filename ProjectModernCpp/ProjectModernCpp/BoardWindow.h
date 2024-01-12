#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <qinputdialog.h>
#include <QGraphicsRectItem>
#include <qmessagebox.h>
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
	void drawLines(QGraphicsScene* scene);
	void drawBaseLines(QGraphicsScene* scene);
	void showMessage();


public slots:
	//void onButtonClicked();
	void onButtonClicked(int x, int y, CircleButton* button);

signals:
	void pointAdded(int x, int y, CircleButton* button);
	void requestPlayerChange();


private:
	Board& m_board;
	std::vector<CircleButton*> m_points;
	std::vector<BridgeLine*> m_lines;
	QGraphicsScene* s;
	Player* m_currentPlayer;
	QGraphicsTextItem* m_currentPlayerText;
	QGraphicsTextItem* m_currentPlayerPointsText;
	QGraphicsTextItem* m_currentPlayerBridgesText;
	QString m_playerNameRed;
	QString m_playerNameBlack;
};

#endif //BOARDWINDOW_H