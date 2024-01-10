#include "Game.h"
#include "MainMenu.h"
#include <fstream>

Game::Game(std::string name1, std::string name2)
	:m_board{ Board() }
	, m_playerRed{ Player(name1, Point::Color::Red) }
	, m_playerBlack{ Player(name2, Point::Color::Black) }
	, m_currentPlayer{ &m_playerRed }
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
	, m_currentPlayer { std::move (other.m_currentPlayer)}
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
	

	showBoard(mainMenu->scene, mainMenu->width(), mainMenu->height(),m_board);
}

void Game::settingsClicked(QGraphicsScene* s) {
	SettingsWindow* settings = new SettingsWindow(s);
}
void Game::initializeGame()
{
	mainMenu = new MainMenu();
	mainMenu->show();
	mainMenu->displayMainMenu();
	connect(mainMenu, SIGNAL(newGameStarted()), this, SLOT(startNewGameSlot()));
	connect(mainMenu, SIGNAL(SettingsClicked()), this, SLOT(settingsSlot()));

}
void Game::startNewGameSlot()
{
	startNewGame();
}

void Game::settingsSlot()
{
	settingsClicked(mainMenu->scene);
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
		m_currentPlayer = &m_playerBlack;
	else
		m_currentPlayer = &m_playerRed;
}

void Game::showBoard(QGraphicsScene* s, int width, int height, Board b)
{
	BoardWindow* board= new BoardWindow(s, width, height,b, m_currentPlayer);
	connect(board, &BoardWindow::pointAdded, this, &Game::onPointAdded);


}

void Game::onPointAdded(int x, int y,CircleButton* button)
{
	if (!button) return;

	Point newPoint(x, y, m_currentPlayer->getColor());
	std::pair position = std::make_pair<size_t, size_t>(x, y);
	if (m_board.getStatus(position)==Board::Status::Empty) {
		button->updateColor(m_currentPlayer->getColor());
		m_board.addPoint(newPoint);
		m_board.makeBridges(newPoint, *m_currentPlayer);

		m_currentPlayer->addPoint(newPoint);

		m_board.makeBridges(newPoint, *m_currentPlayer);



		changeCurrentPlayer();
		emit boardUpdated();
	}
	
}
