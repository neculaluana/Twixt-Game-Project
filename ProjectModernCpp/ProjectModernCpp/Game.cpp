#include "Game.h"
#include <fstream>

void Game::startNewGame() {
	m_board.printBoard();
	std::string name;
	std::cout << "Red player name: ";
	std::cin >> name;
	m_playerRed.setName(name);
	std::cout << "Black player name: ";
	std::cin >> name;
	m_playerBlack.setName(name);
}
void Game::loadGame() {
	std::ofstream fout("twixt.out");
	
}
void Game::makePoint() {
	std::pair<uint8_t, uint8_t> coord;
	std::cout << "x = ";
	std::cin >> coord.first;
	std::cout << "y = ";
	std::cin >> coord.second;
	if (m_board.isPointPossible(coord)) {
		Point p(coord.first, coord.second, m_currentPlayer.getColor());
		m_board.addPoint(p);
		m_board.makeBridges(p, m_currentPlayer);
		m_currentPlayer.addPoint(p);
	}
}
void Game::changeCurrentPlayer() {
	if (m_currentPlayer.getColor() == m_playerRed.getColor())
		m_currentPlayer = m_playerBlack;
	else
		m_currentPlayer = m_playerRed;
}