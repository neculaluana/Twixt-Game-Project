module;
export module Board;
import <vector>;
import <iostream>;
import Point;

namespace twixt {
	export class Board
	{
	public:
		enum class Status {
			Empty=0,
			PlayerRed=1,
			PlayerBlack=2,
			BaseRed=-1,
			BaseBlack=-2
			
		};

		Board(int boardSize=24);
		~Board() = default;

		void boardResize(int boardSize);
		Status getStatus(std::pair<int,int>coordinate)const;
		void setBases(int boardSize);
		int getBoardSize()const;
		void printBoard();

	private:
		int m_boardSize;
		std::vector<std::vector<Status>>m_board;
		std::pair<int, int> m_coordinate;
	};
}