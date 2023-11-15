#pragma once
#include <vector>
#include <iostream>
#include "Point.h"
#include "Bridge.h"
#include "Player.h"


class Board
{
public:
	enum class Status {
		Empty = '.',
		PlayerRed = 'r',
		PlayerBlack = 'b',
		BaseRed = '-',
		BaseBlack = '|'

	};

	Board(int boardSize = 24);
	~Board() = default;

	using Position = std::pair<size_t, size_t>;

	static const size_t kWidth{ 24 }, kHeight{ 24 };
	static const size_t kSize{ kWidth * kHeight };

	void boardResize(int boardSize);
	Status getStatus(const Position& coordinate)const;
	void setBases(int boardSize);
	int getBoardSize()const noexcept;
	void printBoard()const;
	void addPoint(const Point& p);
	bool isBridgePossible(const Point& p1, const Point& p2)const;
	bool isPointPossible(const Position& coordinate)const;
	void makeBridges(const Point& point, Player& player);
private:
	int m_boardSize;
	std::vector<std::vector<Status>> m_board;
};
