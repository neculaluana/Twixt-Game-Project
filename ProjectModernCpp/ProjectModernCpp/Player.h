#pragma once
#include<vector>
#include<cstdint>
#include<string>
#include"Point.h"
#include "Bridge"
class Player
{
public:
	Player(std::string name, Point::Color color);
	~Player() = default;
	Point::Color getColor()const;
	void changeColor();
	void addPoint(const Point& p);
	void removePoint(const Point& p);
	std::vector<Point> getPoints()const;
	std::vector<Bridge> getBridges()const;
	std::string	getName()const;
	void setName(std::string name);

private:

	Point::Color m_color;
	std::vector<Point> m_points;
	std::vector<Bridge> m_bridges;
	std::string m_name;

};
