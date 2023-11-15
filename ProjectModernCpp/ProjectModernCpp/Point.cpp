#include "Point.h"
#include <math.h>
#include <iostream>

Point::Point(int x, int y, Color color)
	:m_coordinates(std::make_pair(x, y))
	,m_color(color)
{}

bool Point::isBridgePossible(const Point& p1, const Point& p2) const
{
	if ((std::abs(p1.getCoordinates().first - p2.getCoordinates().first) == 1 && std::abs(p1.getCoordinates().second - p2.getCoordinates().second) == 2) ||
		(std::abs(p1.getCoordinates().first - p2.getCoordinates().first) == 2 && std::abs(p1.getCoordinates().second - p2.getCoordinates().second) == 1)) {
		return true;
	}
	return false;
}

const Point::Color& Point::getColor() const
{
	return m_color;
}

const std::pair<uint8_t, uint8_t>& Point::getCoordinates() const
{
	return m_coordinates;
}
