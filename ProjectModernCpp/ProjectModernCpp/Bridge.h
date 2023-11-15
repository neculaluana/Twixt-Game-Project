#pragma once
#include "Point.h" 
class Bridge
{
public:
	Bridge(Point startPoint, Point endPoint);
	Bridge(const Bridge& other);

	Point::Color getColor() const;
	Point getStartPoint() const;
	Point getEndPoint() const;
	void setStartPoint(Point p);
	void setEndPoint(Point p);

	~Bridge() = default;

private:
	Point m_startPoint;
	Point m_endPoint;
	Point::Color m_color;
};