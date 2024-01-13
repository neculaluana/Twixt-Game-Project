//#include "Point.h"
//#include <math.h>
//#include <iostream>
//
//Point::Point()
//{
//}
//
//Point::Point(int x, int y, Color color)
//	:m_coordinates(std::make_pair(x, y))
//	,m_color(color)
//{}
//
//Point::Point(const Point& other)
//	:Point{ other.getCoordinates().first, other.getCoordinates().second, other.getColor() }
//{
//}
//
//Point& Point::operator=(const Point& p)
//{
//	if (this != &p)
//	{
//		m_coordinates.first = p.getCoordinates().first;
//		m_coordinates.second = p.getCoordinates().second;
//		m_color = p.getColor();
//	}
//
//	return *this;
//}
//
//Point::Point(Point&& other) noexcept
//	: m_coordinates{ std::move(other.m_coordinates) }
//	, m_color{ other.m_color }
//{
//}
//
//Point& Point::operator=(Point&& p) noexcept
//{
//	if (this != &p)
//	{
//		m_coordinates.first = std::move(p.m_coordinates.first);
//		m_coordinates.second = std::move(p.m_coordinates.second);
//		m_color = p.m_color;
//	}
//
//	return *this;
//}
//
//
//bool Point::isBridgePossible(const Point& p1, const Point& p2) const
//{
//	if ((std::abs(p1.getCoordinates().first - p2.getCoordinates().first) == 1 && std::abs(p1.getCoordinates().second - p2.getCoordinates().second) == 2) ||
//		(std::abs(p1.getCoordinates().first - p2.getCoordinates().first) == 2 && std::abs(p1.getCoordinates().second - p2.getCoordinates().second) == 1)) {
//		return true;
//	}
//	return false;
//}
//
//const Point::Color& Point::getColor() const
//{
//	return m_color;
//}
//
//void Point::setColor(Color color)
//{
//	m_color = color;
//}
//
//const std::pair<uint8_t, uint8_t>& Point::getCoordinates() const
//{
//	return m_coordinates;
//}
//
//bool Point::operator==(const Point& p)
//{
//	return (m_color == p.getColor() && m_coordinates == p.getCoordinates());
//}
//
//bool Point::operator!=(const Point& p)
//{
//	return !(this == &p);
//}
//
//json Point::serialize() const
//{
//	json j;
//	j["x"] = m_coordinates.first;
//	j["y"] = m_coordinates.second;
//	j["color"] = static_cast<int>(m_color);
//	return j;
//}
//
//void Point::deserialize(const json& j)
//{
//
//	if (j.find("x") != j.end() && j.find("y") != j.end() && j.find("color") != j.end())
//	{
//		m_coordinates.first = j["x"];
//		m_coordinates.second = j["y"];
//		m_color = static_cast<Color>(j["color"]);
//	}
//	else
//	{
//		throw std::runtime_error("JSON invalid pentru deserializare Point.");
//	}
//}
//
//bool Point::operator<(const Point& other) const {
//	if (m_coordinates.first == other.m_coordinates.first) {
//		return m_coordinates.second < other.m_coordinates.second;
//	}
//	return m_coordinates.first < other.m_coordinates.first;
//}