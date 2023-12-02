#ifndef  MAINMENU_H
#define MAINMENU_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "ProjectModernCpp.h"

class MainMenu : public QGraphicsView {
	Q_OBJECT;

public:

	MainMenu(QWidget* parent = NULL);

	void displayMainMenu();

	QGraphicsScene* scene;
	//ProjectModernCpp* w;
	
public slots:

	void start();
};

#endif // ! MAINMENU_H
