#pragma once
#include "Player.h"
#include "Board.h"
#include "MainMenu.h"
class Game {
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
	void createBridge(const Point& start, const Point& end);
	void changeCurrentPlayer();
	bool wonGame() const;
	bool drawGame() const;
	~Game() = default;
private:
	MainMenu* mainMenu;
	Player m_playerRed;
	Player m_playerBlack;
	Player* m_currentPlayer;
	Board m_board;
};