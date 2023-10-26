#include<iostream>
#include"Point.h"
#include"Bridge.h"
class Player
{
public:
	Player(Color color);
	~Player() = default;
private:

	Color m_color;
	std::vector<Point> m_points;
	std::vector<Bridge> m_bridges;

};