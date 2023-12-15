#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <vector>
#include "Board.h"
#include "CircleButton.h"
#include "BridgeLine.h"
#include "Game.h"
class BoardWindow : public QObject
{
	Q_OBJECT

public:
	BoardWindow(QGraphicsScene* scene, int width, int height, Game& game, Board& b, Player& currentPlayer);

	void drawLines(QGraphicsScene* scene);
public slots:
	void onButtonClicked();

private:
	Game& m_game;
	Board& m_board;
	Player& m_currentPlayer;
	std::vector<CircleButton*> m_points;
	std::vector<BridgeLine*> m_lines;
	QGraphicsScene* s;
};

#endif //BOARDWINDOW_H