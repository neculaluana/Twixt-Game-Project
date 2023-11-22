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
	~Point() = default;

	Point(const Point& other);
	Point& operator= (const Point& p);
	
	Point(Point&& other) noexcept;
	Point& operator= (Point&& p) noexcept;
	
	const Color& getColor() const;
	void setColor(Color color);
	const std::pair<uint8_t, uint8_t>& getCoordinates() const;
	
	bool isBridgePossible(const Point& p1, const Point& p2) const;
	
	friend bool operator==(const Point& p1, const Point& p2);
	friend bool operator!=(const Point& p1, const Point& p2);

private:
	Point::Color m_color : 1;
	std::pair<uint8_t, uint8_t> m_coordinates;
};