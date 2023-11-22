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
	Player(std::string name, Point::Color color);
	~Player() = default;
	Player(const Player& other);
	Player& operator=(const Player& other);
	Player(Player&& other) noexcept;
	Player& operator=(Player&& other) noexcept;

	Point::Color getColor()const;
	void changeColor();
	void addPoint(const Point& p);
	void addBridge(const Bridge& bridge);
	void removePoint(const Point& p);
	std::vector<Point> getPoints()const;
	std::vector<Bridge> getBridges()const;
	std::string	getName()const;
	void setName(std::string name); 
	friend std::ostream& operator<<(std::ostream& os, const Player& player);
	friend std::istream& operator>>(std::istream& is, Player& player);


private:

	Point::Color m_color;
	std::vector<Point> m_points;
	std::vector<Bridge> m_bridges;
	std::string m_name;

};
