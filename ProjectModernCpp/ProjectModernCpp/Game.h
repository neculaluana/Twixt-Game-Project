#pragma once
#include "Player.h"
#include "Board.h"
#include "MainMenu.h"
#include "BoardWindow.h"
#include <QObject>

#include <QtCore>
#include <QApplication>
#include <QGraphicsScene>
#include <QWidget>
#include <QMessageBox>
#include "SettingsWindow.h"
#include <cstdint>
#include <set>

class Game : public QObject {
	Q_OBJECT;

public:
	Game() = default;

	Game(std::string name1, std::string name2);
	Game(const Game& other);
	Game& operator= (const Game& g);

	Game(Game&& other) noexcept;
	Game& operator= (Game&& g) noexcept;

	const Player& getPlayerRed() const;
	const Player& getPlayerBlack() const;
	const Board& getBoard() const;

	void startNewGame();
	void initializeGame();
	void saveGame(const std::string& filename);
	void loadGame(const std::string& filename);
	void changeCurrentPlayer();
	bool wonGame() const;
	bool drawGame() const;
	void showBoard(QGraphicsScene* s, int width, int height, Board b, bool loadFromFile = false);
	void settingsClicked(QGraphicsScene* s);

	bool isContinuousBridgeLine(const Player& player);
	bool dfs(const Point& current, const std::set<Point>& allPoints, std::set<Point>& visited, size_t boardSize);

	~Game();

public slots:
	void startNewGameSlot(const QString& name1, const QString& name2);
	void settingsSlot();
	void onPointAdded(int x, int y, CircleButton* button);
	void updateSettings(int boardSize, int numberOfBridges, int numberOfPoints);
	void showMainMenu();
	void saveGameSlot();
	void handleChangeCurrentPlayer();
	void startLoadedGameSlot();
signals:
	void boardUpdated();

private:
	BoardWindow* m_boardWindow;
	MainMenu* m_mainMenu;
	SettingsWindow* m_settingsWindow;

	Player m_playerRed;
	Player m_playerBlack;
	Player* m_currentPlayer;
	Board m_board;
	std::function<void()> guiUpdateCallback;
	size_t m_maxPointNumber=50;
	size_t m_maxBridgeNumber=50;
	size_t m_boardSize=24;
	std::pair<uint8_t, uint8_t>m_playersTurn;
	bool isRed;
	//bool isNewGame=false;

};
