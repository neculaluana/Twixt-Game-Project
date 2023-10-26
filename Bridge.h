#include "Point.h"
#include <string>
class Bridge
{
public:
	Bridge(Point firstPoint, Point secondPoint);

private:
	Point m_firstPoint;
	Point m_secondPoint;
	std::string m_color;
};