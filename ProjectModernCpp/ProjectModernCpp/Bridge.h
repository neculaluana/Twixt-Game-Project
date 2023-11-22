#pragma once
#include "Point.h" 
#include <iostream>
class Bridge
{
public:
	Bridge(Point startPoint, Point endPoint);
	Bridge(const Bridge& other);
	Bridge(Bridge&& other)noexcept;
	
	Bridge& operator=(const Bridge& other);
	Bridge& operator=(Bridge&& other)noexcept;
	friend bool operator==(const Bridge& b1, const Bridge& b2);
	friend bool operator!=(const Bridge& b1, const Bridge& b2);
	friend std::ostream& operator<<(std::ostream& os, const Bridge& bridge);
	
	Point::Color getColor() const;
	Point getStartPoint() const;
	Point getEndPoint() const;

	void setStartPoint(Point p);
	void setEndPoint(Point p);

	//bool isValidBridge() const;
	//bool intersects(const Bridge& other) const;
	~Bridge() = default;

private:
	Point m_startPoint;
	Point m_endPoint;
	Point::Color m_color;
};