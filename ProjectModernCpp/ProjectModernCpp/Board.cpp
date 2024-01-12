#include "Board.h"

Board::Board(size_t boardSize) :
	m_boardSize{ boardSize }, m_board{ boardSize, std::vector<Status>{boardSize, Status::Empty} }
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
	: m_boardSize{ std::exchange(other.m_boardSize, 0) }, m_board{ std::move(other.m_board) }
{

}

Board& Board::operator=(Board&& other)noexcept
{
	if (this == &other)
	{
		return *this;
	}

	m_boardSize = std::exchange(other.m_boardSize, 0);
	m_board = std::move(other.m_board);

	return *this;
}

void Board::setBases(size_t boardSize) {
	boardSize = std::min(boardSize, m_boardSize);

	for (size_t i = 0; i < boardSize; ++i) {
		m_board[i][0] = Status::BaseRed;
		m_board[i][boardSize - 1] = Status::BaseRed;
		m_board[0][i] = Status::BaseBlack;
		m_board[boardSize - 1][i] = Status::BaseBlack;
	}
}

void Board::boardResize(size_t boardSize){
	m_boardSize = boardSize;
	m_board.resize(boardSize, std::vector<Status>(boardSize, Status::Empty));
	setBases(boardSize);
}

void Board::setStatus(const Position& coordinate, Board::Status status)
{
	m_board[coordinate.first][coordinate.second] = status;
}


Board::Status Board::getStatus(const Position& coordinate)const
{
	if (coordinate.first < m_boardSize && coordinate.second < m_boardSize)
	{
		return m_board[coordinate.first][coordinate.second];
	}
	else
		return Status::Invalid;
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

void Board::setBoardSize(size_t boardSize)
{
	m_boardSize = boardSize;

}

void Board::serialize(json& j) const {
	j["m_boardSize"] = m_boardSize;
	j["m_board"] = json::array();
	for (const std::vector<Status>& row : m_board) {
		json rowJson = json::array();
		for (const Status& status : row) {
			rowJson.push_back(static_cast<int>(status));
		}
		j["m_board"].push_back(rowJson);
	}
}

void Board::deserialize(const json& j) {
	if (j.contains("m_boardSize")) {
		m_boardSize = j["m_boardSize"].get<size_t>();
	}
	if (j.contains("m_board") && j["m_board"].is_array()) {
		m_board.clear();
		for (const json& rowJson : j["m_board"]) {
			if (rowJson.is_array()) {
				std::vector<Status> row;
				for (const json& statusJson : rowJson) {
					if (statusJson.is_number()) {
						row.push_back(static_cast<Status>(statusJson.get<int>()));
					}
				}
				m_board.push_back(row);
			}
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