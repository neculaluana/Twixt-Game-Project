#include "Point.h"
#include <math.h>
#include <iostream>

Point::Point(int x, int y, Color color)
	:m_coordinates(std::make_pair(x, y))
	,m_color(color)
{}

Point::Point(const Point& other)
	:Point{ other.getCoordinates().first, other.getCoordinates().second, other.getColor() }
{
}

Point& Point::operator=(const Point& p)
{
	if (this != &p)
	{
		m_coordinates.first = p.getCoordinates().first;
		m_coordinates.second = p.getCoordinates().second;
		m_color = p.getColor();
	}

	return *this;
}

Point::Point(Point&& other) noexcept
	: m_coordinates{ std::move(other.m_coordinates) }
	, m_color{ other.m_color }
{
}

Point& Point::operator=(Point&& p) noexcept
{
	if (this != &p)
	{
		m_coordinates.first = std::move(p.m_coordinates.first);
		m_coordinates.second = std::move(p.m_coordinates.second);
		m_color = p.m_color;
	}

	return *this;
}


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

bool Point::operator==(const Point& p)
{
	return (m_color == p.getColor() && m_coordinates == p.getCoordinates());
}

bool Point::operator!=(const Point& p)
{
	return !(this == &p);
}
