#pragma once
#include <iostream>
class Point {
public:
	enum class Color : uint8_t
	{
		Red,
		Black
	};
	Point(int x, int y, Color color);
	Point(const Point& p) = default;
	bool isBridgePossible(const Point& p1, const Point& p2) const;
	const Color& getColor() const;
	const std::pair<uint8_t, uint8_t>& getCoordinates() const;
	~Point() = default;

private:
	Point::Color m_color : 1;
	std::pair<uint8_t, uint8_t> m_coordinates;
};