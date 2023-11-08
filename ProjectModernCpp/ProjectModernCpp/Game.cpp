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