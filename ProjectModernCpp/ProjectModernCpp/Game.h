#pragma once
#include "Player.h"
#include "Board.h"
class Game {
public:
	Game() = default;
	void startNewGame();
	void saveGame(const std::string& filename);
	void loadGame(const std::string& filename);
	void makePoint();
	void createBridge(const Point& start, const Point& end);
	void changeCurrentPlayer();
	bool wonGame() const;
	bool drawGame() const;
	~Game() = default;
private:
	Player m_playerRed;
	Player m_playerBlack;
	Player* m_currentPlayer;
	Board m_board;
};