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
	
	
	const Color& getColor() const;
	const std::pair<uint8_t, uint8_t>& getCoordinates() const;
	~Point() = default;
	Point(const Point& p);
	bool isBridgePossible(const Point& p1, const Point& p2) const;
	
	friend bool operator==(const Point& p1, const Point& p2);
	friend bool operator!=(const Point& p1, const Point& p2);

	Point& operator= (const Point& p);
	void setColor(Color color);
	Point(Point&& other) noexcept;
	Point& operator= (Point&& p) noexcept;

private:
	Point::Color m_color : 1;
	std::pair<uint8_t, uint8_t> m_coordinates;
};