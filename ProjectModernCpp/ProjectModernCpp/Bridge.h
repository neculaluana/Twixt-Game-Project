#pragma once
#include"Point.h"
#include <string>
class Bridge
{
public:
	Bridge(Point startPoint, Point endPoint);
	Color getColor() const;
	Point getStartPoint() const;
	Point getEndPoint() const;
	void setStartPoint();
	void setEndPoint();

	~Bridge() = default;

private:
	Point m_startPoint;
	Point m_endPoint;
	Color m_color;
};