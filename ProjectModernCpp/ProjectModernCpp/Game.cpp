module Game;

using namespace twixt;

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
void Game::makePoint() {
	std::pair<uint8_t, uint8_t> coord;
	std::cout << "x = ";
	std::cin >> coord.first;
	std::cout << "y = ";
	std::cin >> coord.second;
	if (m_board.isPointPossible(coord)) {
		Point p(coord.first, coord.second, m_currentPlayer.getColor());
		m_board.addPoint(p);
		m_board.makeBridge(p);
		m_currentPlayer.addPoint(p);
	}
}