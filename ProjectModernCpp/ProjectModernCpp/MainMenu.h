#ifndef  MAINMENU_H
#define MAINMENU_H

#include <QGraphicsView>
#include <QGraphicsScene>

class MainMenu : public QGraphicsView {
	Q_OBJECT;
public:
	MainMenu(QWidget* parent = NULL);
};

#endif // ! MAINMENU_H
