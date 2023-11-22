#include "Board.h"

Board::Board(size_t boardSize) :
	m_boardSize(boardSize), m_board(boardSize, std::vector<Status>(boardSize, Status::Empty))
{
	setBases(boardSize);
}

Board::Board(const Board& other)
	: m_boardSize{ other.m_boardSize }, m_board{ other.m_board }
{

}

Board& Board::operator=(const Board& other)
{
	if (this == &other)
		return *this;

	m_boardSize = other.m_boardSize;
	m_board = other.m_board;

	return *this;
}

Board::Board(Board&& other)noexcept
	: m_boardSize(std::exchange(other.m_boardSize, 0)), m_board(std::move(other.m_board))
{

}

void Board::setBases(size_t boardSize) {
	boardSize = std::min(boardSize, m_boardSize);

	for (size_t i = 0; i < boardSize; ++i) {
		m_board[i][0] = Status::BaseBlack;
		m_board[i][boardSize - 1] = Status::BaseBlack;
		m_board[0][i] = Status::BaseRed;
		m_board[boardSize - 1][i] = Status::BaseRed;
	}
}

void Board::boardResize(size_t boardSize){
	m_boardSize = boardSize;
	m_board.resize(boardSize, std::vector<Status>(boardSize, Status::Empty));
	setBases(boardSize);
}

Board::Status Board::getStatus(const std::pair<size_t, size_t>&coordinate)const
{
	return m_board[coordinate.first][coordinate.second];
	
}

size_t Board::getBoardSize()const noexcept
{
	return m_boardSize;
}

void Board::printBoard()const
{
	std::cout << *this;

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

bool Board::isPointPossible(const Position& coordinate) const
{
	if (m_board[coordinate.first][coordinate.second] == Board::Status::Empty)
		return true;
	else
		return false;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
	for (size_t y= 0; y < board.getBoardSize(); ++y) {
		for (size_t x = 0; x < board.getBoardSize(); ++x) {
			Board::Status status = board.getStatus({ x, y });
			os << static_cast<char>(status) << ' ';
		}
		os << '\n';
	}
	return os;
}

std::istream& operator>>(std::istream& is, Board& board) {
	char ch;
	for (size_t y = 0; y < board.getBoardSize(); ++y) {
		for (size_t x = 0; x < board.getBoardSize(); ++x) {
			is >> ch;
			Board::Position pos = { x, y };
			switch (ch) {
			case '.': board.m_board[x][y] = Board::Status::Empty; break;
			case 'r': board.m_board[x][y] = Board::Status::PlayerRed; break;
			case 'b': board.m_board[x][y] = Board::Status::PlayerBlack; break;
			case '-': board.m_board[x][y] = Board::Status::BaseRed; break;
			case '|': board.m_board[x][y] = Board::Status::BaseBlack; break;
			default: board.m_board[x][y] = Board::Status::Empty; break;
			}
		}
	}
	return is;
}