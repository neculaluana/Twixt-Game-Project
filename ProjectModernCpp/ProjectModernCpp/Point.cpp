#include "Point.h"
#include <iostream>

Point::Point(int x, int y, Color color)
	:m_coordinates(std::make_pair(x, y))
	,m_color(color)
{
}

bool Point::isBridgePossible(const Point& b) const
{
	
	return false;
}

Color Point::getColor() const
{
	return m_color;
}

std::pair<int, int> Point::getCoordinates() const
{
	return m_coordinates;
}
