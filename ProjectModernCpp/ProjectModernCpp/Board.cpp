module Board;
using namespace twixt;

void Board::boardResize(int boardSize)
{
	m_board.resize(boardSize, std::vector<Status>(boardSize, Status::Empty));
}

Board::Board(int boardSize=24) :
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

Board::Status Board::getStatus(std::pair<int,int>coordinate)const
{
	return m_board[coordinate.first][coordinate.second];
	
}

int Board::getBoardSize()const
{
	return m_boardSize;
}