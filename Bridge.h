#include "Point.h"
#include <string>
class Bridge
{
public:
	Bridge(Point firstPoint, Point secondPoint);
	enum getColor() const;

	~Bridge() = default;

private:
	Point m_firstPoint;
	Point m_secondPoint;
	Color m_color;
};