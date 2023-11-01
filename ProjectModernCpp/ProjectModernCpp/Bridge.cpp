#include "Bridge.h"

Bridge::Bridge(Point startPoint, Point endPoint)
	:m_startPoint{startPoint}
	,m_endPoint{endPoint}
{}

Color Bridge::getColor() const
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
