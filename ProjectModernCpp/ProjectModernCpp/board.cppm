module;
export module Board;
import <vector>;


namespace twixt {
	export class Board
	{
	public:
		enum class Status {
			PlayerRed,
			PlayerBlack,
			BaseRed,
			BaseBlack,
			Empty
		};

		Board(int boardSize=24);
		~Board() = default;

		void boardResize(int boardSize);
		Status getStatus(std::pair<int,int>coordinate)const;
		void setBases(int boardSize);
		int getBoardSize()const;

	private:
		int m_boardSize;
		std::vector<std::vector<Status>>m_board;
		std::pair<int, int> m_coordinate;
	};
}