module Board;
using namespace twixt;

void Board::boardResize(int boardSize)
{
	m_board.resize(boardSize, std::vector<Status>(boardSize, Status::Empty));
	setBases(boardSize);
}

Board::Board(int boardSize) :
	m_boardSize{ boardSize }
{
	boardResize(boardSize);
}

void Board::setBases(int boardSize)
{
	for (int index = 0; index < boardSize; ++index)
	{
		m_board[index][0] = Board::Status::BaseBlack;
		m_board[index][boardSize - 1] = Board::Status::BaseBlack;
		m_board[0][index] = Board::Status::BaseRed;
		m_board[boardSize - 1][index] = Board::Status::BaseRed;
	}

}

Board::Status Board::getStatus(std::pair<uint8_t, uint8_t>coordinate)const
{
	return m_board[coordinate.first][coordinate.second];
	
}

int Board::getBoardSize()const
{
	return m_boardSize;
}

void Board::printBoard()
{
	for (const auto& lin : m_board)
	{
		for (const auto& col : lin)
			std::cout << static_cast<char>(col)<<" ";
		std::cout << std::endl;
	}

}
void Board::addPoint(const Point& p)
{
	if (p.getColor() == Point::Color::Red)
		m_board[p.getCoordinates().first][p.getCoordinates().second] = Board::Status::PlayerRed;
	else 
		m_board[p.getCoordinates().first][p.getCoordinates().second] = Board::Status::PlayerBlack;

}

bool Board::isBridgePossible(const Point& p1, const Point& p2)const
{
	if (((std::abs(p1.getCoordinates().first - p2.getCoordinates().first) == 1 && std::abs(p1.getCoordinates().second - p2.getCoordinates().second) == 2) ||
		(std::abs(p1.getCoordinates().first - p2.getCoordinates().first) == 2 && std::abs(p1.getCoordinates().second - p2.getCoordinates().second) == 1)) && 
		(p1.getColor() == p2.getColor()))
	{
		return true;
	}
	return false;

}


void Board::makeBridges(const Point& point, Player& player )
{
	std::vector<Point> points = player.getPoints();
	for (const auto& pnt : points)
	{
		
		if (Board::isBridgePossible(point,pnt))
		{
			Bridge bridge(point,pnt);
			player.addBridge(bridge);
		}
	}
}

bool Board::isPointPossible(const std::pair<uint8_t, uint8_t>& coordinate) const
{
	if (m_board[coordinate.first][coordinate.second] == Board::Status::Empty)
		return true;
	else
		return false;
}
