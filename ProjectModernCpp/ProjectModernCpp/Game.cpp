#include "Game.h"
#include <fstream>

Game::Game(std::string name1, std::string name2)
	:m_board{ Board() }
	, m_playerRed{ Player(name1, Point::Color::Red) }
	, m_playerBlack{ Player(name2, Point::Color::Black) }
{}

Game::Game(const Game& other)
	:m_playerRed{ other.getPlayerRed() }
	, m_playerBlack{ other.getPlayerBlack() }
	, m_board{ other.getBoard() }
{
}

Game& Game::operator=(const Game& g)
{
	if (this != &g)
	{
		m_playerRed = g.getPlayerRed();
		m_playerBlack = g.getPlayerBlack();
		m_board = g.getBoard();
	}

	return *this;
}

Game::Game(Game&& other) noexcept
	: m_playerRed{ std::move(other.m_playerRed) }
	, m_playerBlack{ std::move(other.m_playerBlack) }
	, m_board{ std::move(other.m_board) }
{
}

Game& Game::operator=(Game&& g) noexcept
{
	if (this != &g)
	{
		m_playerRed = std::move(g.m_playerRed);
		m_playerBlack = std::move(g.m_playerBlack);
		m_board = std::move(g.m_board);
	}

	return *this;
}

const Player& Game::getPlayerRed() const
{
	return m_playerRed;
}

const Player& Game::getPlayerBlack() const
{
	return m_playerBlack;
}

const Board& Game::getBoard() const
{
	return m_board;
}

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
	//file << m_currentPlayer->getColor();

	file.close();

}
void Game::loadGame(const std::string& filename) {
	std::ofstream file(filename, std::ios::in | std::ios::binary);
	if (!file) {
		std::cerr << "Unable to open file for loading game state." << std::endl;
		return;
	}

	//file >> m_board;
	//file >> m_playerRed;
	//file >> m_playerBlack;
	//file >> m_currentPlayer->getColor();

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