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

Bridge& Bridge::operator=(Bridge & other)
{
	if (this != &other) 
	{ 
		m_startPoint = other.m_startPoint; 
		m_endPoint = other.m_endPoint;     
		m_color = other.m_color;           
	}
	return *this;
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
