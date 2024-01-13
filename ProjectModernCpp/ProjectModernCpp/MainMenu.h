#ifndef  MAINMENU_H
#define MAINMENU_H


#include "BoardWindow.h"
#include "SettingsWindow.h"
#include"MenuButton.h"
#include <qfiledialog.h>
#include <regex>

class MainMenu : public QGraphicsView {
	Q_OBJECT;

public:

	MainMenu(QWidget* parent = NULL);

	void displayMainMenu();

	void setIsNewGame(bool a);
	void setSettings(bool b);
	bool getIsNewGame();
	bool getSettingsClicked();
	QGraphicsScene* scene;
	void removeAllItems();
signals:
	void newGameStarted(const QString& playerRedName, const QString& playerBlackName);
	void SettingsClicked();
	void loadGameStarted();
public slots:

	void newGame();
	void load();
	void settings();
private:
	bool isNewGame;
	bool settingsClicked;
	MenuButton* playButton;
	MenuButton* loadButton;
	MenuButton* settingsButton;
	MenuButton* quitButton;
	QGraphicsPixmapItem* image;
	QLineEdit* playerNameRedInput;
	QLineEdit* playerNameBlackInput;

};

#endif // ! MAINMENU_H
