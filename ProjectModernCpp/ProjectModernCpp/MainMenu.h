#ifndef  MAINMENU_H
#define MAINMENU_H

#include <QGraphicsView>
#include <QGraphicsScene>

class MainMenu : public QGraphicsView {
	Q_OBJECT;

public:

	MainMenu(QWidget* parent = NULL);

	void displayMainMenu();

	QGraphicsScene* scene;
	
public slots:

	void start();
};

#endif // ! MAINMENU_H
