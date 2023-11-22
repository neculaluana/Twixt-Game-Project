#include "Bridge.h"


Bridge::Bridge(Point startPoint, Point endPoint)
	:m_startPoint{startPoint}
	,m_endPoint{endPoint}
	,m_color(startPoint.getColor())
{}

Bridge::Bridge(const Bridge & other)
	:m_startPoint(other.getStartPoint())
	,m_endPoint(other.getEndPoint())
	,m_color(other.getColor())
{}

Bridge& Bridge::operator=(const Bridge & other)
{
	if (this != &other) 
	{ 
		m_startPoint = other.m_startPoint; 
		m_endPoint = other.m_endPoint;     
		m_color = other.m_color;           
	}
	return *this;
}

Bridge::Bridge(Bridge&& other) noexcept
	: m_startPoint(std::move(other.m_startPoint)),
	m_endPoint(std::move(other.m_endPoint)),
	m_color(std::move(other.m_color))
{
}



bool operator==(const Bridge& b1, const Bridge& b2)
{
	return (((b1.getStartPoint() == b2.getStartPoint()) &&
		(b1.getEndPoint() == b2.getEndPoint())) || ((b1.getStartPoint() == b2.getEndPoint()) &&
			(b1.getEndPoint() == b2.getStartPoint()))) &&
		(b1.getColor() == b2.getColor());
}

bool operator!=(const Bridge& b1, const Bridge& b2)
{
	return !(b1 == b2);
}


Point::Color Bridge::getColor() const
{
	return m_color;
}

Point Bridge::getStartPoint() const
{
	return m_startPoint;
}

Point Bridge::getEndPoint() const
{
	return m_endPoint;
}

void Bridge::setStartPoint(Point p)
{
	m_startPoint = p;
}

void Bridge::setEndPoint(Point p)
{
	m_endPoint = p;
}
