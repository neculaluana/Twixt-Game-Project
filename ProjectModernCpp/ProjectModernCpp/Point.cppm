module;
#include <cstdint>

export module Point;
import <iostream>;

namespace twixt {
	export class Point {
	public:
		enum class Color
		{
			Red,
			Black
		};
		Point(int x, int y, Color color);
		bool isBridgePossible(const Point& b) const;
		Color getColor() const;
		std::pair<int, int> getCoordinates() const;

	private:
		Color m_color;
		std::pair<int, int> m_coordinates;
	};
}