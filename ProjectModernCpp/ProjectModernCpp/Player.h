#pragma once
#include<vector>
#include<iostream>
#include<cstdint>
#include<string>
#include"Point.h"
#include"Bridge.h"

class Player
{
public:
	//Player(std::string name, Point::Color color);
	Player(std::string name, Point::Color color, size_t maxPointsCount=50, size_t maxBridgesCount=50);
	~Player() = default;
	Player(const Player& other);
	Player& operator=(const Player& other);
	Player(Player&& other) noexcept;
	Player& operator=(Player&& other) noexcept;


	Point::Color getColor()const;
	void changeColor();
	void addPoint(const Point& p);
	void addBridge(const Bridge& bridge);
	void removeBridge(const Bridge& p);
	bool getPlayerTurn();
	void setPlayerTurn(bool turn);
	std::vector<Point> getPoints()const;
	std::vector<Bridge> getBridges()const;
	std::string	getName()const;
	void setName(std::string name); 
	void serialize(json& j) const;
	void deserialize(const json& j);
	bool getfirstMoveMade();
	void setfirstMoveMade(bool moveMade);
	void popFirstPoint();

	uint8_t getPointsSize();
	uint8_t getBridgesSize();
	size_t getMaxPointsCount();
	size_t getMaxBridgesCount();
	void setMaxPointsCount(size_t maxPoints);
	void setMaxBridgesCount(size_t maxBridges);
	friend std::ostream& operator<<(std::ostream& os, const Player& player);
	friend std::istream& operator>>(std::istream& is, Player& player);

private:

	Point::Color m_color;
	std::vector<Point> m_points;
	std::vector<Bridge> m_bridges;
	std::string m_name;
	bool m_playerTurn;
	size_t m_maxPointsCount=50;
	size_t m_maxBridgesCount=50;
	bool m_firstMoveMade = false;


};
