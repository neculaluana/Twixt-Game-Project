module Bridge;

using namespace twixt;

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
