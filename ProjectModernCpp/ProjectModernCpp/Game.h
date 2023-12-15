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
	void makePoint();
	void changeCurrentPlayer();
	bool wonGame() const;
	bool drawGame() const;
	void showBoard(QGraphicsScene* s, int width, int height, Board b);
	
	~Game() = default;

public slots:
	void startNewGameSlot();
	void onPointAdded(int x, int y, CircleButton* button);
signals:
	void boardUpdated();
private:
	MainMenu* mainMenu;
	Player m_playerRed;
	Player m_playerBlack;
	Player* m_currentPlayer;
	Board m_board;
	std::function<void()> guiUpdateCallback;
};