#include "Board.h"

Board::Board(size_t boardSize) :
	m_boardSize{ boardSize }
{
	boardResize(boardSize);
}
void Board::boardResize(size_t boardSize)
{
	m_board.resize(boardSize, std::vector<Status>(boardSize, Status::Empty));
	setBases(boardSize);
}



void Board::setBases(size_t boardSize)
{
	for (int indexBoard = 0; indexBoard < boardSize; ++indexBoard)
	{
		m_board[indexBoard][0] = Board::Status::BaseBlack;
		m_board[indexBoard][boardSize - 1] = Board::Status::BaseBlack;
		m_board[0][indexBoard] = Board::Status::BaseRed;
		m_board[boardSize - 1][indexBoard] = Board::Status::BaseRed;
	}

}

Board::Status Board::getStatus(const std::pair<size_t, size_t>&coordinate)const
{
	return m_board[coordinate.first][coordinate.second];
	
}

size_t Board::getBoardSize()const
{
	return m_boardSize;
}

void Board::printBoard()const
{
	

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
	for (size_t y = 0; y < board.getBoardSize(); ++y) {
		for (size_t x = 0; x < board.getBoardSize(); ++x) {
			Board::Status status = board.getStatus({ x, y });
			os << static_cast<char>(status) << ' ';
		}
		os << '\n';
	}
	return os;
}

std::istream& operator>>(std::istream& is, Board& board)
{
	char ch;
	for (size_t i = 0; i < board.getBoardSize(); ++i) {
		for (size_t j = 0; j < board.getBoardSize(); ++j) {
			is >> ch;
			Board::Status status;
			switch (ch) {
			case '.': status = Board::Status::Empty; break;
			case 'r': status = Board::Status::PlayerRed; break;
			case 'b': status = Board::Status::PlayerBlack; break;
			case '-': status = Board::Status::BaseRed; break;
			case '|': status = Board::Status::BaseBlack; break;
			default: status = Board::Status::Empty; break;
			}
			board.m_board[i][j] = status;
		}
	}
	return is;

}