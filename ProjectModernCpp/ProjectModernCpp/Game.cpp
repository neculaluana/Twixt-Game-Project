#include "Game.h"
#include "MainMenu.h"
#include <fstream>

Game::Game(std::string name1, std::string name2)
	: m_board{ Board() }
	, m_playerRed{ Player(name1, Point::Color::Red) }
	, m_playerBlack{ Player(name2, Point::Color::Black) }
	, m_currentPlayer{ &m_playerRed }
	, m_mainMenu(nullptr)
	, m_settingsWindow(nullptr)
{
	
	initializeGame();
	m_playerBlack.setfirstMoveMade(true);
	connect(m_mainMenu, &MainMenu::newGameStarted, this, &Game::startNewGameSlot);
	connect(m_mainMenu, SIGNAL(SettingsClicked()), SLOT(settingsSlot()));
	connect(m_mainMenu, SIGNAL(loadGameStarted()), SLOT(startLoadedGameSlot()));



}

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

Game::~Game() {
	if (m_settingsWindow) {
		m_settingsWindow->disconnect();
		m_settingsWindow->deleteLater();
	}
	if (m_mainMenu) {
		m_mainMenu->disconnect();
		m_mainMenu->deleteLater();
	}
}

Game::Game(Game&& other) noexcept
	: m_playerRed{ std::move(other.m_playerRed) }
	, m_playerBlack{ std::move(other.m_playerBlack) }
	, m_board{ std::move(other.m_board) }
	, m_currentPlayer{ std::move(other.m_currentPlayer) }
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

	showBoard(m_mainMenu->scene, m_mainMenu->width(), m_mainMenu->height(), m_board);
}


void Game::initializeGame()
{
	m_mainMenu = new MainMenu();
	m_mainMenu->show();

}
void Game::startNewGameSlot(const QString& name1, const QString& name2)
{
	m_board.setBoardSize(m_boardSize);
	m_playerRed.setMaxPointsCount(m_maxPointNumber);
	m_playerBlack.setMaxPointsCount(m_maxPointNumber);
	m_playerRed.setMaxBridgesCount(m_maxBridgeNumber);
	m_playerBlack.setMaxBridgesCount(m_maxBridgeNumber);
	m_playerRed.setName(name1.toStdString());
	m_playerBlack.setName(name2.toStdString());
	startNewGame();
}
void Game::saveGame(const std::string& filename) {
	json j;

	m_playerRed.serialize(j["playerRed"]);
	m_playerBlack.serialize(j["playerBlack"]);
	m_board.serialize(j["board"]);

	std::ofstream file(filename);
	if (file.is_open()) {
		file << j.dump(4);
		file.close();
	}
	else {
		std::cerr << "Eroare la deschiderea fi?ierului de salvare." << std::endl;
	}
}
void Game::loadGame(const std::string& filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		std::string file_contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		json j = json::parse(file_contents);

		m_playerRed.deserialize(j["playerRed"]);
		m_playerBlack.deserialize(j["playerBlack"]);
		m_board.deserialize(j["board"]);
		for (const auto& redb : m_playerRed.getBridges())
		{
			m_board.pushBackBridge(redb);
		}
		for (const auto& blackb : m_playerBlack.getBridges())
		{
			m_board.pushBackBridge(blackb);
		}
		if (m_playerRed.getPlayerTurn())
			m_currentPlayer = &m_playerRed;
		else
			m_currentPlayer = &m_playerBlack;
		file.close();
	}
	else {
		std::cerr << "Eroare la deschiderea fisierului de încãrcare." << std::endl;
	}

}

void Game::changeCurrentPlayer() {

	m_currentPlayer->setPlayerTurn(false);
	if (m_currentPlayer == &m_playerRed)
		m_currentPlayer = &m_playerBlack;
	else
		m_currentPlayer = &m_playerRed;
	m_currentPlayer->setPlayerTurn(true);
	if (m_boardWindow) {
		m_boardWindow->setCurrentPlayer(m_currentPlayer);
	}
}

void Game::showBoard(QGraphicsScene* s, int width, int height, Board b, bool loadFromFile)
{

	m_mainMenu->removeAllItems();
	if (loadFromFile)
	{
		if (m_currentPlayer == &m_playerRed)
			m_otherPlayer = &m_playerBlack;
		else
			m_otherPlayer = &m_playerRed;

		m_boardWindow = new BoardWindow(s, width, height, b, m_currentPlayer, loadFromFile,m_otherPlayer );
	}
	else
		m_boardWindow = new BoardWindow(s, width, height, b, m_currentPlayer);
	connect(m_boardWindow, &BoardWindow::pointAdded, this, &Game::onPointAdded);
	connect(m_boardWindow, &BoardWindow::saveGameRequested, this, &Game::saveGameSlot);


	
	
	connect(m_boardWindow, &BoardWindow::requestPlayerChange, this, &Game::handleChangeCurrentPlayer);
}


void Game::onPointAdded(int x, int y, CircleButton* button)
{
	if (!button) return;
	if ((*m_currentPlayer).getColor() == Point::Color::Black)
	{
		qDebug() << "rosie";
		isRed = false;
		if (isRed == false)
			qDebug() << "isRed este fals";
	}
	if ((*m_currentPlayer).getColor() == Point::Color::Red)
	{
		qDebug() << "negru";
		isRed = true;
		if (isRed == true)
			qDebug() << "isRed este true";
	}


	std::pair position = std::make_pair<size_t, size_t>(x, y);
	if (m_board.getStatus(position) == Board::Status::BaseRed)
		qDebug() << "baza rosie";

	if (m_board.getStatus(position) == Board::Status::BaseBlack)
		qDebug() << "baza neagra";


	if (m_board.getStatus(position) == Board::Status::BaseRed && (*m_currentPlayer).getColor() == Point::Color::Black)
	{
		button->resetColor();


		return;
	}
	if (m_board.getStatus(position) == Board::Status::BaseBlack && (*m_currentPlayer).getColor() == Point::Color::Red)
	{
		button->resetColor();
		return;
	}
	if (m_board.getStatus(position) == Board::Status::BaseRed && (*m_currentPlayer).getColor() == Point::Color::Red)
	{
		Point newPoint(x, y, (*m_currentPlayer).getColor());

		button->updateColor(Point::Color::Red);
		m_board.addPoint(newPoint);
		m_board.makeBridges(newPoint, *m_currentPlayer);

		(*m_currentPlayer).addPoint(newPoint);

		
		emit boardUpdated();

		m_playersTurn.second++;
		qDebug() << m_playersTurn.second << '\n';
	}
	else
		if (m_board.getStatus(position) == Board::Status::Empty) {
			Point newPoint(x, y, (*m_currentPlayer).getColor());

			button->updateColor((*m_currentPlayer).getColor());

			if (m_currentPlayer->getColor() == Point::Color::Red)
			{
				m_playersTurn.first++;
				qDebug() << m_playersTurn.first << '\n';
			}
			else
				if (m_currentPlayer->getColor() == Point::Color::Black)
				{
					m_playersTurn.second++;
					qDebug() << m_playersTurn.second << '\n';
				}
			m_board.addPoint(newPoint);
			m_board.makeBridges(newPoint, *m_currentPlayer);

			(*m_currentPlayer).addPoint(newPoint);

			

			emit boardUpdated();
		}
		else if (m_board.getStatus(position) == Board::Status::BaseBlack && (*m_currentPlayer).getColor() == Point::Color::Black)
		{
			Point newPoint(x, y, (*m_currentPlayer).getColor());

			button->updateColor(Point::Color::Black);
			m_board.addPoint(newPoint);
			m_board.makeBridges(newPoint, *m_currentPlayer);

			(*m_currentPlayer).addPoint(newPoint);

			
			emit boardUpdated();
			m_playersTurn.first++;
			qDebug() << m_playersTurn.first << '\n';

		}


	if (isContinuousBridgeLine(*m_currentPlayer))
	{
		QString winnerName = QString::fromStdString(m_currentPlayer->getName());
		QString message = winnerName + " has won the game!";

		QMessageBox msgBox;
		msgBox.setWindowTitle("Game Over");
		msgBox.setText(message);
		msgBox.addButton("Quit", QMessageBox::AcceptRole);

		if (msgBox.exec() == QMessageBox::AcceptRole) {
			QApplication::quit(); // This will close the application
		}
	}
	changeCurrentPlayer();

}
void Game::settingsSlot()
{
	settingsClicked(m_mainMenu->scene);
}

void Game::settingsClicked(QGraphicsScene* s) {
	if (!m_settingsWindow) {
		m_mainMenu->removeAllItems();
		m_settingsWindow = new SettingsWindow(s);
		connect(m_settingsWindow, &SettingsWindow::settingsSaved, this, &Game::showMainMenu);
		connect(m_settingsWindow, &SettingsWindow::settingsChanged, this, &Game::updateSettings);
		connect(m_settingsWindow, &SettingsWindow::settingsCanceled, this, &Game::showMainMenu);
		
	}
	else
	{
		m_mainMenu->removeAllItems();
		m_settingsWindow->showAllItems();
	}

	
}



void Game::updateSettings(int boardSize, int numberOfPoints, int numberOfBridges) {
	m_boardSize = boardSize;
	m_maxPointNumber = numberOfPoints;
	m_maxBridgeNumber = numberOfBridges;
	m_board.boardResize(boardSize);
}

void Game::showMainMenu() {
	if (m_mainMenu) {
		m_mainMenu->displayMainMenu();
	}
}

void Game::saveGameSlot() {
	saveGame("savegame.json");
}

void Game::handleChangeCurrentPlayer()
{
	
	Point initalPoint = m_playerRed.getPoints()[0];
	m_playerRed.popFirstPoint();
	initalPoint.setColor(Point::Color::Black);
	
	
	std::string nameRed = m_playerRed.getName();
	std::string nameBlack = m_playerBlack.getName();

	Player* aux = &m_playerRed;
	m_playerRed = m_playerBlack;

	m_playerBlack = *aux;
	m_playerRed.changeColor();

	m_playerRed.addPoint(initalPoint);
	m_playerRed.setName(nameBlack);
	m_playerBlack.setName(nameRed);
}



void Game::startLoadedGameSlot() {
	loadGame("savegame.json");
	showBoard(m_mainMenu->scene, m_mainMenu->width(), m_mainMenu->height(), m_board, true);
}

bool Game::isContinuousBridgeLine(const Player& player) {
	std::set<Point> allPoints;

	for (const auto& p : player.getPoints())
		allPoints.insert(p);

	std::set<Point> visited;

	for (const auto& point : allPoints) {
		if ((player.getColor() == Point::Color::Red && point.getCoordinates().second == 0) ||
			(player.getColor() == Point::Color::Black && point.getCoordinates().first == 0)) { // Starting from the first row
			if (dfs(point, allPoints, visited, m_boardSize)) {
				return true;
			}
		}
	}

	return false;
}

bool Game::dfs(const Point& current, const std::set<Point>& allPoints, std::set<Point>& visited, size_t boardSize) {
	if ((current.getColor() == Point::Color::Red && current.getCoordinates().second == boardSize - 1) ||
		(current.getColor() == Point::Color::Black && current.getCoordinates().first == boardSize - 1)) {
		return true;
	}

	visited.insert(current);

	for (const auto& point : allPoints) {
		if (visited.find(point) == visited.end() && current.isBridgePossible(current, point)) {
			if (dfs(point, allPoints, visited, boardSize)) {
				return true;
			}
		}
	}

	return false;
}