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

	void boardResize(int boardSize);
	Status getStatus(std::pair<uint8_t, uint8_t>coordinate)const;
	void setBases(int boardSize);
	int getBoardSize()const;
	void printBoard();
	void addPoint(const Point& p);
	bool isBridgePossible(const Point& p1, const Point& p2)const;
	bool isPointPossible(const std::pair<uint8_t, uint8_t>& coordinate)const;
	void makeBridges(const Point& point, Player& player);
private:
	int m_boardSize;
	std::vector<std::vector<Status>> m_board;
};
