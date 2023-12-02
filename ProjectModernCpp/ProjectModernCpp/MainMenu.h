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
	void showBoard(QGraphicsScene* s, int width, int height);
	
public slots:

	void start();
	void load();
};

#endif // ! MAINMENU_H
