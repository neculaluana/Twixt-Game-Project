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

private:
	Color m_color;
	std::pair<int, int> m_coordinates;
};