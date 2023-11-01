#include <iostream>
enum class Color
{
	Red, 
	Black
};
class Point
{
public:
	Point(int x, int y, Color color);
	bool isBridgePossible(const Point& b) const;
	Color getColor() const;
	std::pair<int, int> getCoordinates() const;

private:
	Color m_color;
	std::pair<int, int> m_coordinates;
};