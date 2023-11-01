#include <vector>
class Board {

public:

	Board();
	
	Board(int size);

	~Board() = default;

private: 
	int m_size;
	std::vector<std::vector<int>>m_board;
};