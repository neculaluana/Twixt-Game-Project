#ifdef GAMELOGIC_EXPORTS
#define BOARD_API _declspec(dllexport)
#else
#define BOARD_API _declspec(dllimport)
#endif // GAMELOGIC_EXPORTS

#pragma once

#include "Player.h"


class BOARD_API Board
{
public:
	enum class Status {
		Empty,
		PlayerRed,
		PlayerBlack,
		BaseRed,
		BaseBlack,
		Invalid

	};

	using Position = std::pair<size_t, size_t>;

	Board(size_t boardSize = 24);
	Board(const Board& other);
	Board& operator= (const Board& other);

	Board(Board&& other)noexcept;
	Board& operator= (Board&& other)noexcept;

	~Board() = default;


	Status getStatus(const Position& coordinate)const;
	void setStatus(const Position& coordinate, Board::Status status);
	void setBases(size_t boardSize);
	void boardResize(size_t boardSize);
	size_t getBoardSize() const noexcept;

	void printBoard()const;
	void addPoint(const Point& p);
	bool isBridgePossible(const Point& p1, const Point& p2)const;
	bool isPointPossible(const Position& coordinate)const;
	void makeBridges(const Point& point, Player& player);
	void setBoardSize(size_t boardSize);
	void serialize(json& j) const;
	void deserialize(const json& j);
	bool isBridgesIntersection(const Bridge& existingBridge, const Bridge& futureBridge);
	void pushBackBridge(Bridge bridge);

	friend std::ostream& operator<<(std::ostream& os, const Board& board);
	friend std::istream& operator>>(std::istream& is, Board& board);


private:
	size_t m_boardSize;
	std::vector<std::vector < Status >> m_board;
	std::vector<Bridge> m_bridges;
};
