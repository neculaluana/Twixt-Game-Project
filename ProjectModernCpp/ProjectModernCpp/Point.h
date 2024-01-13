#pragma once
#include <iostream>

#include "json.hpp"
using json = nlohmann::json;

class Point {
public:
	enum class Color : uint8_t
	{
		Red,
		Black,
		Debug
	};
	Point();
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
	
	bool operator==(const Point& p);
	bool operator!=(const Point& p);
	bool operator<(const Point& other) const;

	json serialize() const;
	void deserialize(const json& j);
private:
	Point::Color m_color : 1;
	std::pair<uint8_t, uint8_t> m_coordinates;
};