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
			Empty='.',
			PlayerRed='r',
			PlayerBlack='b',
			BaseRed='-',
			BaseBlack='|'
			
		};

		Board(int boardSize=24);
		~Board() = default;

		void boardResize(int boardSize);
		Status getStatus(std::pair<int,int>coordinate)const;
		void setBases(int boardSize);
		int getBoardSize()const;
		void printBoard();
		void addPoint(const Point& p);
		bool isBridgePossible(const Point& p1, const Point& p2)const;
	private:
		int m_boardSize;
		std::vector<std::vector<Status>>m_board;
		std::pair<int, int> m_coordinate;
	};
}