#pragma once
#include "Player.h"
#include "board.h"
class Game {
public:
	Game() = default;
	void startNewGame();
	void loadGame();
	void makePoint();
	void changeCurrentPlayer();
	bool wonGame() const;
	bool drawGame() const;
	~Game() = default;
private:
	Player m_playerRed;
	Player m_playerBlack;
	Player m_currentPlayer;
	Board m_board;
};