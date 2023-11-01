module;
export module Board;
#include <vector>

namespace twixt {
	export class Board
	{
	public:
		enum class Status {
			Player_1,
			Player_2,
			Empty
		};

	private:
		int m_boardSize;
		std::vector<std::vector<Status>>board;
		
	};
}