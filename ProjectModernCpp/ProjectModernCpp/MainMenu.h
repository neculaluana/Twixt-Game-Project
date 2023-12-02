#ifndef  MAINMENU_H
#define MAINMENU_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "ProjectModernCpp.h"
#include "BoardWindow.h"

class MainMenu : public QGraphicsView {
	Q_OBJECT;

public:

	MainMenu(QWidget* parent = NULL);

	void displayMainMenu();

	QGraphicsScene* scene;
	//ProjectModernCpp* w;
	void setIsNewGame(bool a);
	bool getIsNewGame();
signals:
	void newGameStarted();
public slots:

	void newGame();
	void load();
private:
	bool isNewGame;
};

#endif // ! MAINMENU_H
