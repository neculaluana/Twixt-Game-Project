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
	

	showBoard(m_mainMenu->scene, m_mainMenu->width(), m_mainMenu->height(),m_board);
}


void Game::initializeGame()
{
	m_mainMenu = new MainMenu();
	m_mainMenu->show();
	m_mainMenu->displayMainMenu();
	connect(m_mainMenu, SIGNAL(newGameStarted()), this, SLOT(startNewGameSlot()));
	connect(m_mainMenu, SIGNAL(SettingsClicked()), this, SLOT(settingsSlot()));

}
void Game::startNewGameSlot()
{
	startNewGame();
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
	if (m_boardWindow) {
		m_boardWindow->setCurrentPlayer(m_currentPlayer);
	}
}

void Game::showBoard(QGraphicsScene* s, int width, int height, Board b)
{
	m_boardWindow = new BoardWindow(s, width, height,b, m_currentPlayer);
	connect(m_boardWindow, &BoardWindow::pointAdded, this, &Game::onPointAdded);


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


	}else	
	if (m_board.getStatus(position) == Board::Status::BaseRed && m_currentPlayer->getColor() == Point::Color::Red)
	{

		button->updateColor(m_currentPlayer->getColor());
		m_board.addPoint(newPoint);
		m_board.makeBridges(newPoint, *m_currentPlayer);

		m_currentPlayer->addPoint(newPoint);

		m_board.makeBridges(newPoint, *m_currentPlayer);
		changeCurrentPlayer();
		
	}
	else if(m_board.getStatus(position) == Board::Status::BaseBlack && m_currentPlayer->getColor() == Point::Color::Black)
	{

		button->updateColor(m_currentPlayer->getColor());
		m_board.addPoint(newPoint);
		m_board.makeBridges(newPoint, *m_currentPlayer);

		m_currentPlayer->addPoint(newPoint);

		m_board.makeBridges(newPoint, *m_currentPlayer);
		changeCurrentPlayer();

	}

	
		emit boardUpdated();
	}
	
void Game::settingsSlot()
{
	settingsClicked(m_mainMenu->scene);
}

void Game::settingsClicked(QGraphicsScene* s) {
	if (!m_settingsWindow) {
		m_settingsWindow = new SettingsWindow(s);
		bool success1 = connect(m_settingsWindow, SIGNAL(settingsSaved()), this, SLOT(showMainMenu()));
		bool success2 = connect(m_settingsWindow, SIGNAL(settingsCanceled()), this, SLOT(showMainMenu()));
		bool success3 = connect(m_settingsWindow, SIGNAL(settingsChanged(int, int, int)), this, SLOT(updateSettings(int, int, int)));
		if (!success1) {
			qDebug() << "Connection failed save!";
		}
		if (!success1) {
			qDebug() << "Connection failed cancel!";
		}
		if (!success1) {
			qDebug() << "Connection failed change!";
		}
		connect(m_settingsWindow, &SettingsWindow::finished, [this]() {
			m_settingsWindow = nullptr;
			});
	}
	else {
		
		if (m_settingsWindow->isHidden()) {
			m_settingsWindow->show();
		}
		else {
			m_settingsWindow->raise();
			m_settingsWindow->activateWindow();
		}
	}
}

void Game::updateSettings(int boardSize, int numberOfPoints, int numberOfBridges) {
	m_boardSize = boardSize;
	m_maxPointNumber = numberOfPoints;
	m_maxBridgeNumber = numberOfBridges;
}

void Game::showMainMenu() {
	if (m_mainMenu) {
		m_mainMenu->displayMainMenu();
	}
}

