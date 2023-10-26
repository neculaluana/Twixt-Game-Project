#include "Bridge.h"

Bridge::Bridge(Point firstPoint, Point secondPoint)
	:m_firstPoint{firstPoint}
	,m_secondPoint{secondPoint}
{}

Color Bridge::getColor() const
{
	return m_color;
}
