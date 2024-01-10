#ifndef  MAINMENU_H
#define MAINMENU_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "ProjectModernCpp.h"
#include "BoardWindow.h"
#include "SettingsWindow.h"

class MainMenu : public QGraphicsView {
	Q_OBJECT;

public:

	MainMenu(QWidget* parent = NULL);

	void displayMainMenu();

	QGraphicsScene* scene;
	//ProjectModernCpp* w;
	void setIsNewGame(bool a);
	void setSettings(bool b);
	bool getIsNewGame();
	bool getSettingsClicked();
signals:
	void newGameStarted();
	void SettingsClicked();
public slots:

	void newGame();
	void load();
	void settings();
private:
	bool isNewGame;
	bool settingsClicked;
};

#endif // ! MAINMENU_H
