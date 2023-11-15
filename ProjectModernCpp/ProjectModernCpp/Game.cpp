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
void Game::saveGame(const std::string& filename)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);
	if (!file) {
		std::cerr << "Unable to open file for saving game state." << std::endl;
		return;
	}

	file << m_board;
	file << m_playerRed;
	file << m_playerBlack;
	file << m_currentPlayer->getColor();

	file.close();

}
void Game::loadGame(const std::string& filename) {
	std::ofstream file(filename, std::ios::in | std::ios::binary);
	if (!file) {
		std::cerr << "Unable to open file for loading game state." << std::endl;
		return;
	}

	file >> m_board;
	file >> m_playerRed;
	file >> m_playerBlack;
	file >> m_currentPlayer->getColor();

	file.close();
}
void Game::makePoint() {
	std::pair<uint8_t, uint8_t> coord;
	std::cout << "x = ";
	std::cin >> coord.first;
	std::cout << "y = ";
	std::cin >> coord.second;
	if (m_board.isPointPossible(coord)) {
		Point p(coord.first, coord.second, (*m_currentPlayer).getColor());
		m_board.addPoint(p);
		m_board.makeBridges(p, *m_currentPlayer);
		(*m_currentPlayer).addPoint(p);
	}
}
void Game::changeCurrentPlayer() {
	if ((*m_currentPlayer).getColor() == m_playerRed.getColor())
		*m_currentPlayer = m_playerBlack;
	else
		*m_currentPlayer = m_playerRed;
}